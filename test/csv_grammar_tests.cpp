#include <catch.hpp>
#include <string>
#include <fstream>
#include <iterator>

#include "csv_grammar.hpp"
#include "find_zip_data.hpp"

namespace qi = boost::spirit::qi;

TEST_CASE("The csv parsing grammar")
{
  using iter_t = boost::spirit::istream_iterator;
  
  std::ifstream ifs{csv_file_path};
  ifs >> std::noskipws;

  REQUIRE(ifs.is_open());

  auto begin = iter_t{ifs};
  auto end   = iter_t{};

  csv_grammar_t<iter_t> csv_grammar;

  csv_rows_t output;

  qi::phrase_parse(
    begin, end,
    csv_grammar,
    qi::space,
    output);

  // current number of usable rows in the CSV file
  // brittle test but it does ensure correctness when
  // refactoring and it's not likely the CSV will change
  // for the time being
  REQUIRE(output.size() == 43191);
}