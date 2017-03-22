#include "catch.hpp"

#include <iterator>
#include <iostream>

#include <boost/geometry.hpp> 
#include <boost/geometry/index/rtree.hpp> 

TEST_CASE("The Boost geographic points")
{
  namespace bg  = boost::geometry;
  namespace bgi = bg::index;

  using coordinate_system = bg::cs::geographic<bg::degree>;

  using point_t = bg::model::point<double, 2, coordinate_system>;

  SECTION("should be somewhat useful")
  {
    point_t const a{ -12, 34 };
    point_t const b{ 13, -37 };

    REQUIRE(bg::distance(a, b) != 0);
  }

  SECTION("should work with an rtree as well")
  {
    using rtree_t = bgi::rtree<point_t, bgi::linear<16>>;

    point_t const a{ -12, 34 };
    point_t const b{ 13, -37 };

    rtree_t rtree{};

    rtree.insert(a);
    rtree.insert(b);

    std::vector<point_t> points;

    REQUIRE(rtree.size() == 2);

    rtree.query(
      bgi::satisfies([&](point_t const& p) -> bool
      {
        return bg::distance(a, p) != 0;
      }),
      std::back_inserter(points));

    REQUIRE(points.size() == 1);
  }
}