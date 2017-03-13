#include "catch.hpp"

#include "coord.hpp"
#include "coord_tree.hpp"

#include <vector>
#include <random>
#include <iterator>

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

    std::vector<point_t> pts;
    
    auto const pt = *tree.begin();

    tree.query(boost::geometry::index::nearest(pt, 10), std::back_inserter(pts));

    std::cout << "Nearest 10 neighbors to: " << get<0>(pt) << ", " << get<1>(pt) << "\n\n";
    for (auto const& point : pts) {
      std::cout << get<0>(point) << ", " << get<1>(point) << "\n";
    }
	}
}