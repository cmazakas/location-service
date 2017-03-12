#ifndef COORD_TREE_HPP_
#define COORD_TREE_HPP_

#include "coord.hpp"
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/index/parameters.hpp> 

using Parameters = boost::geometry::index::linear<10, 1>;

using coord_tree_t = boost::geometry::index::rtree<point_t, Parameters>;

#endif // COORD_TREE_HPP_