#include <catch.hpp>
#include <string>
#include <fstream>
#include <iterator>

#include "csv_grammar.hpp"
#include "find_zip_data.hpp"

namespace qi = boost::spirit::qi;

TEST_CASE("The csv parsing grammar")
{
  auto const csv_input = std::string{
    "\"00210\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\"" // 0
    "\"00211\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\"" // 1
    "\"00212\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\"" // 2
    "\"00213\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\"" // 3
    "\"00214\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\"" // 4
    "\"00215\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\"" // 5
    "\"00501\",\"Holtsville\",\"NY\",\"40.922326\",\"-72.637078\",\"-5\",\"1\"" // 6
    "\"00544\",\"Holtsville\",\"NY\",\"40.922326\",\"-72.637078\",\"-5\",\"1\"" // 7    
  };

  auto const begin = csv_input.begin();
  auto const end   = csv_input.end();

  using iter_t = decltype(csv_input.begin());
  csv_grammar_t<iter_t> csv_grammar;

  csv_rows_t output;

  qi::phrase_parse(
    begin, end,
    csv_grammar,
    qi::space,
    output);

  REQUIRE(output.size() == 8);
}