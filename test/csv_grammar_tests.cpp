#include <catch.hpp>
#include <string>
#include <fstream>
#include <iterator>

#include "csv_grammar.hpp"

namespace qi = boost::spirit::qi;

TEST_CASE("The csv parsing grammar")
{
  using iter_t = boost::spirit::istream_iterator;

  std::ifstream ifs{"C:\\Users\\christian\\clc\\location-service\\zip_data\\zipcode.csv"};
  ifs >> std::noskipws;

  REQUIRE(ifs.is_open());

  auto begin = iter_t{ifs};
  auto end   = iter_t{};

  csv_grammar_t<iter_t> csv_grammar;
  std::vector<csv_row_t> output;

  qi::phrase_parse(
    begin, end,
    csv_grammar,
    qi::space,
    output);

  REQUIRE(output.size() > 0);

  for (auto const& csv_row : output) {
    std::cout << csv_row.city << '\n';
  }


}