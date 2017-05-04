#include <catch.hpp>
#include <iostream>

#include "csv_row_to_point.hpp"
#include "equal.hpp"

namespace
{
  constexpr double const pi = 3.14159265358979323846;

  auto radian_to_degree(double const radians) -> double
  {
    return (180.0/pi) * radians;
  }

  struct coord_t
  {
    latitude_t  lat;
    longitude_t lon;

    auto operator==(coord_t const& other) const -> bool
    {
      return eq(lat, other.lat) && eq(lon, other.lon);
    }
  };

  auto operator<<(std::ostream& os, coord_t const& coord) -> std::ostream&
  {
    os << "{ lat: " << coord.lat << ", lon: " << coord.lon << " }";
    return os;
  }
}

TEST_CASE("The csv row to point conversion routine")
{
  SECTION("should be able to accurately convert to (x, y, z)")
  {
    auto const csv_row = csv_row_t{
      zip_t{"00210"}, 
      city_t{"Portsmouth"}, 
      state_t{"NH"}, 
      latitude_t{43.005895}, 
      longitude_t{-71.013202}, 
      timezone_t{-5}, 
      dst_t{1}};

    auto const p = csv_row_to_point(csv_row);

    auto const x = p.get<0>();
    auto const y = p.get<1>();
    auto const z = p.get<2>();

    auto const r = sqrt(
      pow(x, 2) + pow(y, 2) + pow(z, 2));

    auto const inclination = radian_to_degree(acos(z/r));
    auto const azimuth     = radian_to_degree(atan2(y, x));

    auto const lat = inclination - 90.0;
    auto const lon = azimuth     - 180.0;

    auto const coord          = coord_t{latitude_t{lat},  longitude_t{lon}};
    auto const expected_coord = coord_t{latitude_t{43.005895}, longitude_t{-71.013202}};

    REQUIRE(r == 6'371'000);
    REQUIRE(coord == expected_coord);
  }
}