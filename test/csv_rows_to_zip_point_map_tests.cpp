#include <catch.hpp>
#include <string>
#include <vector>

#include "csv_rows_to_zip_point_map.hpp"
#include "csv_rows_from_range.hpp"

TEST_CASE("The conversion from csv rows to a zip-point hash table")
{
  SECTION("should behave as we expect it to")
  {
    auto const csv_input = std::string{
      "\"00210\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\""
      "\"00211\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\""
      "\"00212\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\""
      "\"00213\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\""
      "\"00214\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\""
      "\"00215\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\""
      "\"00501\",\"Holtsville\",\"NY\",\"40.922326\",\"-72.637078\",\"-5\",\"1\"" 
      "\"00544\",\"Holtsville\",\"NY\",\"40.922326\",\"-72.637078\",\"-5\",\"1\""    
    };


    auto const csv_rows = csv_rows_from_range(
      csv_input.begin(), 
      csv_input.end());

    auto const zip_point_map = csv_rows_to_zip_point_map(csv_rows);

    REQUIRE(csv_rows.size() > 0);
    REQUIRE(zip_point_map.size() == csv_rows.size());

    auto const expected_zips = std::vector<zip_t>{
      zip_t{"00210"}, 
      zip_t{"00211"}, 
      zip_t{"00212"}, 
      zip_t{"00213"}, 
      zip_t{"00214"}, 
      zip_t{"00215"}, 
      zip_t{"00501"}, 
      zip_t{"00544"}};
  }
}