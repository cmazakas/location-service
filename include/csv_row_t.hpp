#ifndef CSV_ROW_T_HPP_
#define CSV_ROW_T_HPP_

#include <string>
#include <vector>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/serialization/strong_typedef.hpp>

BOOST_STRONG_TYPEDEF(std::string, zip_t);
BOOST_STRONG_TYPEDEF(std::string, city_t);
BOOST_STRONG_TYPEDEF(std::string, state_t);

BOOST_STRONG_TYPEDEF(double, latitude_t);
BOOST_STRONG_TYPEDEF(double, longitude_t);

BOOST_STRONG_TYPEDEF(int, timezone_t);
BOOST_STRONG_TYPEDEF(int, dst_t);

struct csv_row_t
{
  zip_t   zip;
  city_t  city;
  state_t state;

  latitude_t  latitude;
  longitude_t longitude;

  timezone_t timezone;
  dst_t      dst;
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


using csv_rows_t = std::vector<csv_row_t>;

#endif // CSV_ROW_T_HPP_