#include <exception>
#include "find_zip_data.hpp"

namespace fs = std::experimental::filesystem;

fs::path csv_file_path = ([](void) -> fs::path 
{
  auto from_relative_path = fs::path{__FILE__}.parent_path();
  from_relative_path /= fs::path{"../zip_data/zipcode.csv"};

  if (from_relative_path.empty()) {
    throw std::invalid_argument{"Could not locate zipcode.csv file!!!"};
  }

  return from_relative_path;
})();