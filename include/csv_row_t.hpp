#ifndef CSV_ROW_T_HPP_
#define CSV_ROW_T_HPP_

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

struct csv_row_t
{
  std::string zip;
  std::string city;
  std::string state;

  double latitude;
  double longitude;

  int timezone;
  int dst;
};

BOOST_FUSION_ADAPT_STRUCT(
  csv_row_t,
  (decltype(csv_row_t::zip),   zip)
  (decltype(csv_row_t::city),  city)
  (decltype(csv_row_t::state), state)

  (decltype(csv_row_t::latitude),  latitude)
  (decltype(csv_row_t::longitude), longitude)

  (decltype(csv_row_t::timezone), timezone)
  (decltype(csv_row_t::dst),      dst))

#endif // CSV_ROW_T_HPP_