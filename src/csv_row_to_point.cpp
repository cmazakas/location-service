#include <cmath>
#include "csv_row_to_point.hpp"

//double const static earth_radius = 6'371'000; // meters

namespace
{
  constexpr double const earth_radius = 6'371'000; // meters

  constexpr double const pi = 3.14159265358979323846;

  auto degree_to_radian(double const degrees) -> double
  {
    return (pi/180.0) * degrees;
  }
}

auto csv_row_to_point(csv_row_t const& csv_row) -> point_t
{
  auto const inclination = degree_to_radian(csv_row.latitude  + 90.0);
  auto const azimuth     = degree_to_radian(csv_row.longitude + 180.0);

  auto const x = earth_radius * sin(inclination) * cos(azimuth);
  auto const y = earth_radius * sin(inclination) * sin(azimuth);
  auto const z = earth_radius * cos(inclination);

  return { x, y, z };
}