#include <boost/iterator/transform_iterator.hpp>

#include "csv_to_rtree.hpp"
#include "csv_row_to_point.hpp"

namespace
{
  auto csv_row_to_rtree_value_type(csv_row_t const& csv_row) -> typename rtree_t::value_type
  {
    return {csv_row_to_point(csv_row), csv_row};
  }
}

auto csv_rows_to_rtree(csv_rows_t const& csv_rows) -> rtree_t
{
  using input_iter_t = decltype(csv_rows.begin());
 
  auto const begin = boost::make_transform_iterator(
    csv_rows.begin(), csv_row_to_rtree_value_type);

  auto const end = begin + csv_rows.size();

  return rtree_t{begin, end};
}