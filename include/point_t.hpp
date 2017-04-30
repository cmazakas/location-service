#ifndef POINT_T_HPP_
#define POINT_T_HPP_

#include <iostream>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp> 

using coordinate_type   = double;
using coordinate_system = boost::geometry::cs::cartesian;

size_t const static dimension_count = 3;

using point_t = boost::geometry::model::point<
  coordinate_type, dimension_count, coordinate_system
>;

auto operator<<(std::ostream& os, point_t const& p) -> std::ostream&;

#endif // POINT_T_HPP_
