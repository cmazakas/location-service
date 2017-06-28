#include "csv_to_rtree.hpp"
#include "csv_rows_to_zip_point_map.hpp"

#include <pplx/pplxtasks.h>
#include <cpprest/http_msg.h>

auto handle_http_req(
  rtree_t                 const& rtree,
  zip_point_map_t         const& zip_point_map,
  web::http::http_request const& req) 
-> pplx::task<void>;