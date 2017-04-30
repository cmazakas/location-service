#include <catch.hpp>
#include <iostream>

#include "csv_row_to_point.hpp"

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

    auto const inclination = acos(z/r);
    auto const azimuth     = atan(y/x);

    auto const latitude  = inclination - 90.0;
    auto const longitude = azimuth - 180.0;

    REQUIRE(r         == 6'371'000);
    //REQUIRE(latitude  == 43.005895);
    //REQUIRE(longitude == -71.013202);
  }
}