#include <cmath>
#include "csv_row_to_point.hpp"

double const static earth_radius = 6'371'000; // meters

auto csv_row_to_point(csv_row_t const& csv_row) -> point_t
{
  auto const inclination = csv_row.latitude  + 90.0;
  auto const azimuth     = csv_row.longitude + 180.0;

  auto const x = earth_radius * sin(inclination) * cos(azimuth);
  auto const y = earth_radius * sin(inclination) * sin(azimuth);
  auto const z = earth_radius * cos(inclination);

  return { x, y, z };
}