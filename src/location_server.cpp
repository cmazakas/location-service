#include "location_server.hpp"
#include "csv_parser.hpp"
#include "find_zip_data.hpp"

namespace
{
  using config_t        = web::http::experimental::listener::http_listener_config;
  using http_request_t  = web::http::http_request;
  using http_response_t = web::http::http_response;
  using uri_t           = web::uri;
}

location_server_t::location_server_t(void)
{
  auto const csv_rows = get_csv_location_data(csv_file_path.string());

  rtree_ = csv_rows_to_rtree(csv_rows);

  http_listener_ = http_listener_t{
    uri_t{
      utility::string_t{U("http://localhost:3000")}},
    config_t{}};

  // we only need one route handler for this micro-service!
  // simply hit the server with /?zip=...radius=...
  // and the service will retrive all zip codes within the given
  // radius 
  http_listener_.support([](http_request_t http_request) -> void
  {
    auto const query_params = uri_t::split_query(
      http_request
        .relative_uri()
        .to_string());

    auto const iter_to_zip    = query_params.find(utility::string_t{U("zip")});
    auto const iter_to_radius = query_params.find(utility::string_t{U("radius")});

    if (iter_to_zip == query_params.end() || iter_to_radius == query_params.end()) {
      auto http_response = http_response_t{web::http::status_code{400}};
      //http_response.set_

    } else {
      auto http_response = http_response_t{web::http::status_code{200}};

      http_response.set_body(U("asasdfasdfasdf"));

      http_request.reply(http_response);
    }
  });
}

auto location_server_t::open(void) -> pplx::task<void>
{
  return http_listener_.open();
}

auto location_server_t::close(void) -> pplx::task<void>
{
  return http_listener_.close();
}