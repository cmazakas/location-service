#ifndef CSV_TO_RTREE_HPP_
#define CSV_TO_RTREE_HPP_

#include <utility>

#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/index/parameters.hpp>

#include "point_t.hpp"
#include "csv_row_t.hpp"

using rtree_t = boost::geometry::index::rtree<
  std::pair<point_t, csv_row_t>,
  boost::geometry::index::linear<256>
>;

auto csv_rows_to_rtree(csv_rows_t const& csv_rows) -> rtree_t;

#endif // CSV_TO_RTREE_HPP_
