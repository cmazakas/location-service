#include "location_server.hpp"
#include "csv_parser.hpp"
#include "find_zip_data.hpp"

namespace
{
  using config_t        = web::http::experimental::listener::http_listener_config;
  using http_request_t  = web::http::http_request;
  using http_response_t = web::http::http_response;
  using uri_t           = web::uri;
  using string_t        = utility::string_t;

  namespace bgi = boost::geometry::index;
}

location_server_t::location_server_t(void)
{
  auto const csv_rows = get_csv_location_data(csv_file_path.string());

  rtree_         = csv_rows_to_rtree(csv_rows);
  zip_point_map_ = csv_rows_to_zip_point_map(csv_rows);

  http_listener_ = http_listener_t{
    uri_t{string_t{U("http://localhost:3000")}},
    config_t{}};

  // we only need one route handler for this micro-service!
  // simply hit the server with /?zip=95833&radius=30
  // and the service will retrive all zip codes within the given
  // radius (which is assumed to be meters)
  //http_listener_.support([this](http_request_t http_request) -> void
  //{
  //  auto const relative_uri = http_request.relative_uri();

  //  auto const query_params = uri_t::split_query(relative_uri.to_string());

  //  auto const iter_to_zip    = query_params.find(string_t{U("zip")});
  //  auto const iter_to_radius = query_params.find(string_t{U("radius")});

  //  if (iter_to_zip == query_params.end() || iter_to_radius == query_params.end()) {
  //    auto http_response = http_response_t{web::http::status_code{400}};

  //    http_response.set_reason_phrase(
  //      web::http::reason_phrase{U("Invalid arguments supplied to route")});

  //    http_request.reply(http_response);

  //  } else {

  //    auto const zip = (*iter_to_zip).second;

  //    // TODO: add exception handling to this because it throws :P
  //    auto const radius = stod((*iter_to_radius).second);

  //    auto closest_csv_rows = std::vector<typename rtree_t::value_type>{};
  //    closest_csv_rows.reserve(128);

  //    rtree_.query(bgi::nearest(point_t{}, 30), std::back_inserter(closest_csv_rows));

  //    auto http_response = http_response_t{web::http::status_code{200}};
  //    http_response.set_body(U("asasdfasdfasdf"));

  //    http_request.reply(http_response);
  //  }
  //});
}

auto location_server_t::open(void) -> pplx::task<void>
{
  return http_listener_.open();
}

auto location_server_t::close(void) -> pplx::task<void>
{
  return http_listener_.close();
}