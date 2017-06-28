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
  using exception_t = web::http::http_exception;

  using uri_parse_result_t = boost::variant<
    std::pair<double, zip_t>,
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

    auto const zip    = query_params.find(U("zip"));
    auto const radius = query_params.find(U("radius"));

    if (zip == end || radius == end) {
      return exception_t{400, U("Invalid query parameters supplied to route")};
    }

    try {
    
      auto const parsed_zip = std::stod((*zip).second);

      return std::make_pair(parsed_zip, zip_t{std::string{""}});

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
          value_t{csv_row.longitude})
      });
  }

  auto rtree_entry_to_json(typename rtree_t::value_type const& tree_entry) 
  -> web::json::value
  {
    using std::get;
    using boost::get;

    auto const csv_row = get<csv_row_t>(tree_entry);

    return web::json::value::object();
  }
}

auto handle_http_req(
  rtree_t                 const& rtree,
  zip_point_map_t         const& zip_point_map,
  web::http::http_request const& req) 
-> pplx::task<void>
{
  using std::get;
  using boost::get;
  using boost::geometry::index::nearest;

  using pair_t        = std::pair<double, zip_t>;
  using status_code_t = web::http::status_code;

  auto const zip_and_radius_or_exception = get_zip_radius(req.relative_uri());
  auto const zip_and_radius              = get<pair_t>(zip_and_radius_or_exception);

  auto tree_entries = std::vector<typename rtree_t::value_type>{};
  tree_entries.reserve(256);

  auto iter_to_zip = zip_point_map.find(get<zip_t>(zip_and_radius));
  if (iter_to_zip == zip_point_map.end()) {
    return req.reply(status_code_t{400}, U("Invalid zip code supplied to server!"));
  }

  auto const point = get<point_t>(*iter_to_zip);

  rtree.query(
    nearest(point, 40),
    std::back_inserter(tree_entries));



  return {};
}