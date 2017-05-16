#include <boost/iterator/transform_iterator.hpp>

#include "csv_rows_to_zip_point_map.hpp"
#include "csv_row_to_point.hpp"

namespace
{
  auto csv_row_to_zip_point_pair(csv_row_t const& csv_row) 
    -> typename zip_point_map_t::value_type
  {
    return {csv_row.zip, csv_row_to_point(csv_row)};
  }
}

auto csv_rows_to_zip_point_map(csv_rows_t const& csv_rows) -> zip_point_map_t
{
  auto const begin = boost::make_transform_iterator(csv_rows.begin(), csv_row_to_zip_point_pair);
  auto const end   = begin + csv_rows.size();

  return zip_point_map_t{begin, end};
}