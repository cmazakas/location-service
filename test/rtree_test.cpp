#include "catch.hpp"

#include "coord.hpp"
#include "coord_tree.hpp"

#include <random>
#include <boost/geometry.hpp>

TEST_CASE("The Boost rtree")
{
	SECTION("should be, to some degree, useful")
	{
    coordinate_type const min = -180;
    coordinate_type const max = 180;

    std::mt19937_64 random_engine;
    std::uniform_real_distribution<coordinate_type> random_distribution_coordinate{min, max};

    auto const make_point = [&](void) -> point_t
    {
      return {
        random_distribution_coordinate(random_engine),
        random_distribution_coordinate(random_engine)
      };
    };

    coord_tree_t tree;

    size_t const num_pts = 1000;

    for (size_t i = 0; i < num_pts; ++i) {
      tree.insert(make_point());
    }

    REQUIRE(tree.size() == num_pts);

    using boost::geometry::get;

    for (auto const& node : tree) {
      std::cout << get<0>(node) << ", " << get<1>(node) << "\n";
    }
	}
}