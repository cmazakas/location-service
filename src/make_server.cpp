#include "csv_parser.hpp"
#include "csv_to_rtree.hpp"
#include "make_server.hpp"

auto make_server(std::string const& filename) -> http_listener_t
{
  auto const rtree = csv_rows_to_rtree(get_csv_location_data(filename));


  return http_listener_t{};
}