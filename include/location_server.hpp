#ifndef LOCATION_SERVER_HPP_
#define LOCATION_SERVER_HPP_

#include "csv_to_rtree.hpp"
#include <cpprest/http_listener.h>
#include <cpprest/asyncrt_utils.h>

struct location_server_t
{
private:
  using http_listener_t = web::http::experimental::listener::http_listener;

  using config_t = web::http::experimental::listener::http_listener_config;

  rtree_t         rtree_;
  http_listener_t http_listener_;

public:

  location_server_t(void)
  {
    using uri_t = web::uri;

    http_listener_ = http_listener_t{
      uri_t{
        utility::string_t{U("http://localhost:3000")}},
      config_t{}};


  }

  auto open(void) -> pplx::task<void>
  {
    return http_listener_.open();
  }

  auto close(void) -> pplx::task<void>
  {
    return http_listener_.close();
  }
};

#endif // LOCATION_SERVER_HPP_