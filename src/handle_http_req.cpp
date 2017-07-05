#include <string>
#include <utility>
#include <iterator>
#include <vector>

#include <boost/variant.hpp>
#include <boost/iterator/transform_iterator.hpp>

#include "csv_row_t.hpp"
#include "handle_http_req.hpp"

#include <cpprest/json.h>

namespace 
{
  using pair_t        = std::pair<double, zip_t>;
  using status_code_t = web::http::status_code;
  using exception_t   = web::http::http_exception;

  using uri_parse_result_t = boost::variant<
    pair_t,
    exception_t>;

  auto get_zip_radius(web::http::uri const& uri) -> uri_parse_result_t
  {
    using uri_t = web::http::uri;
    
    auto const relative_path = uri.path();

    if (relative_path != U("/")) {
      return exception_t{400, U("Incorrect path given. Simply use \"/\"")};
    }

    auto const query_params = uri_t::split_query(uri.query());

    if (query_params.size() != 2) {
      return exception_t{400, U("Invalid query parameters supplied to route")};
    }

    auto const end = query_params.end();

    auto const zip_iter    = query_params.find(U("zip"));
    auto const radius_iter = query_params.find(U("radius"));

    if (zip_iter == end || radius_iter == end) {
      return exception_t{400, U("Invalid query parameters supplied to route")};
    }

    try {
    
      auto const radius = std::stod((*radius_iter).second);

      auto const& zip = (*zip_iter).second;

      return std::make_pair(
        radius, 
        zip_t{std::string{zip.begin(), zip.end()}});

    } catch (std::exception const& e) {

      return exception_t{400, utility::conversions::to_string_t(e.what())};
    }
  }

  auto csv_row_to_json(csv_row_t const& csv_row) -> web::json::value
  {
    using value_t = web::json::value;
    
    using utility::conversions::to_string_t;

    using vec_t = std::vector<
      std::pair<
        utility::string_t, 
        value_t>
    >;

    return value_t::object(
      vec_t{
        std::make_pair(
          U("zip"), 
          value_t{to_string_t(csv_row.zip)}),
        std::make_pair(
          U("city"),
          value_t{to_string_t(csv_row.city)}),
        std::make_pair(
          U("state"),
          value_t{to_string_t(csv_row.state)}),
        std::make_pair(
          U("longitude"),
          value_t{csv_row.longitude}),
        std::make_pair(
          U("latitude"),
          value_t{csv_row.latitude})
      });
  }

  auto rtree_entry_to_json(typename rtree_t::value_type const& tree_entry) 
  -> web::json::value
  {
    using std::get;
    using boost::get;

    return csv_row_to_json(get<csv_row_t>(tree_entry));
  }

  auto convert_radius_and_point_to_box(
    double const radius,
    point_t const& point)
  ->  boost::geometry::model::box<point_t>
  {
    using boost::geometry::get;

    auto const r = radius;

    auto const x = get<0>(point);
    auto const y = get<1>(point);
    auto const z = get<2>(point);

    return {
      point_t{x - r, y - r, z - r},
      point_t{x + r, y + r, z + r}};
  }

  struct req_visitor_t : public boost::static_visitor<pplx::task<void>>
  {
    rtree_t                 const& rtree;
    zip_point_map_t         const& zip_point_map;
    web::http::http_request const& req;

    req_visitor_t(
      rtree_t                 const& rt, 
      zip_point_map_t         const& zipm, 
      web::http::http_request const& r) 
      : rtree{rt}, zip_point_map{zipm}, req{r}
    {}

    auto operator()(exception_t const& exception) -> pplx::task<void>
    {
      return req.reply(status_code_t{200}, exception.what());
    }

    auto operator()(pair_t const& zip_and_radius) -> pplx::task<void>
    {
      using std::get;
      using boost::get;
      using boost::geometry::index::within;

      auto tree_entries = std::vector<typename rtree_t::value_type>{};
      tree_entries.reserve(256);

      auto iter_to_zip = zip_point_map.find(get<zip_t>(zip_and_radius));
      if (iter_to_zip == zip_point_map.end()) {
        return req.reply(status_code_t{400}, U("Invalid zip code supplied to server!"));
      }

      auto const point = get<point_t>(*iter_to_zip);

      rtree.query(
        within(convert_radius_and_point_to_box(get<double>(zip_and_radius), point)),
        std::back_inserter(tree_entries));

      auto const json_iter_begin = boost::make_transform_iterator(
        tree_entries.begin(), 
        rtree_entry_to_json);

      auto const json_vector = std::vector<web::json::value>{
        json_iter_begin,
        json_iter_begin + tree_entries.size()};

      return req.reply(
        status_code_t{200},
        web::json::value::array(json_vector));
    }
  };
}

auto handle_http_req(
  rtree_t                 const& rtree,
  zip_point_map_t         const& zip_point_map,
  web::http::http_request const& req) 
-> pplx::task<void>
{
  auto zip_and_radius_or_exception = get_zip_radius(req.relative_uri());

  auto visitor = req_visitor_t{rtree, zip_point_map, req};

  return boost::apply_visitor(
    visitor,
    zip_and_radius_or_exception);  
}