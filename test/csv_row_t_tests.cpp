#include <catch.hpp>
#include <boost/spirit/include/qi.hpp>
#include "csv_row_t.hpp"

TEST_CASE("The CSV row type")
{
  SECTION("should be constructible with values")
  {
    auto const csv_row = csv_row_t{
      "95833",
      "Sacramento",
      "CA",
      12.213,
      1337.001,
      5,
      1
    };
  }
}