#include "location_server.hpp"
#include "csv_parser.hpp"

namespace
{
  using config_t        = web::http::experimental::listener::http_listener_config;
  using http_request_t  = web::http::http_request;
  using http_response_t = web::http::http_response;
  using uri_t           = web::uri;
}

location_server_t::location_server_t(void)
{
  auto const csv_rows = get_csv_location_data(
    std::string{"C:\\Users\\christian\\clc\\location-service\\zip_data\\zipcode.csv"});

  rtree_ = csv_rows_to_rtree(csv_rows);

  http_listener_ = http_listener_t{
    uri_t{
      utility::string_t{U("http://localhost:3000")}},
    config_t{}};

  http_listener_.support([](http_request_t http_request) -> void
  {
    auto http_response = http_response_t{web::http::status_code{200}};

    http_response.set_body(U("asasdfasdfasdf"));

    http_request.reply(http_response);
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