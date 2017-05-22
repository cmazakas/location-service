#include <catch.hpp>
#include <string>

#include "csv_parser.hpp"
#include "find_zip_data.hpp"

TEST_CASE("The CSV parser")
{
  SECTION("should handle bad filepaths...")
  {
    // I guess this could potentially be a valid filepath...
    auto const filepath = std::string{"qwerqwerqwerqwer"};

    auto const csv_rows = get_csv_location_data(filepath);

    REQUIRE(csv_rows.size() == 0);
  }

  SECTION("should be able to parse and read in our csv file")
  {
    auto const filepath = csv_file_path.string();
    auto const csv_rows = get_csv_location_data(filepath);

    REQUIRE(csv_rows.size() == 43191);
  }
}