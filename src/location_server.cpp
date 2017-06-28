#include "location_server.hpp"
#include "csv_parser.hpp"
#include "find_zip_data.hpp"
#include "handle_http_req.hpp"

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
  http_listener_.support(
    [this](http_request_t const& req) -> pplx::task<void>
    {
      return handle_http_req(
        this->rtree_, 
        this->zip_point_map_, 
        req);
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