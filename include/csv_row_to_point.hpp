#ifndef CSV_ROW_TO_POINT_HPP_
#define CSV_ROW_TO_POINT_HPP_

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp> 
#include "csv_row_t.hpp"

using coordinate_type   = double;
using coordinate_system = boost::geometry::cs::cartesian;

size_t const static dimension_count = 3;

using point_t = boost::geometry::model::point<
  coordinate_type, dimension_count, coordinate_system
>;

auto csv_row_to_point(csv_row_t const& csv_row) -> point_t;

#endif // CSV_ROW_TO_POINT_HPP_