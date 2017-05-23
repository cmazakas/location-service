#ifndef LOCATION_SERVER_HPP_
#define LOCATION_SERVER_HPP_

#include <functional>

#include "csv_to_rtree.hpp"
#include "csv_rows_to_zip_point_map.hpp"

#include <cpprest/http_listener.h>
#include <cpprest/asyncrt_utils.h>

struct location_server_t
{
private:

  using http_listener_t = web::http::experimental::listener::http_listener;
 
  rtree_t         rtree_;
  http_listener_t http_listener_;
  zip_point_map_t zip_point_map_;

public:

  location_server_t(void);

  auto open(void)  -> pplx::task<void>;
  auto close(void) -> pplx::task<void>;
};

#endif // LOCATION_SERVER_HPP_