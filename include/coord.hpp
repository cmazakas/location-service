#ifndef COORD_HPP_
#define COORD_HPP_

#include <boost/geometry/geometries/point.hpp> 
#include <boost/geometry/core/cs.hpp> 

size_t const static DimensionCount = 2;

using coordinate_type   = double;
//using CoordinateSystem = boost::geometry::cs::geographic<boost::geometry::degree>;
using CoordinateSystem = boost::geometry::cs::cartesian;

using point_t = boost::geometry::model::point<
  coordinate_type, DimensionCount, CoordinateSystem
>;

#endif // COORD_HPP_