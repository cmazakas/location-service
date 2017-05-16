#ifndef CSV_ROWS_TO_ZIP_POINT_MAP_HPP_
#define CSV_ROWS_TO_ZIP_POINT_MAP_HPP_

#include <unordered_map>
#include <functional>

#include "csv_row_t.hpp"
#include "point_t.hpp"

namespace std
{
  template <>
  struct hash<zip_t>
  {
    auto operator()(zip_t const& zip) const noexcept -> size_t
    {
      return hash<string>{}(static_cast<string>(zip));
    }
  };
}

using zip_point_map_t = std::unordered_map<zip_t, point_t>;

auto csv_rows_to_zip_point_map(csv_rows_t const& csv_rows) -> zip_point_map_t;

#endif // CSV_ROWS_TO_ZIP_POINT_MAP_HPP_