#include <catch.hpp>
#include <string>

#include "csv_to_rtree.hpp"
#include "csv_grammar.hpp"

TEST_CASE("The csv to rtree function")
{
  SECTION("should be able to construct an rtree from a csv")
  {
    namespace qi = boost::spirit::qi;

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

    using iter_t = decltype(csv_input.begin());

    auto csv_rows = csv_rows_t{};

    auto const begin = csv_input.begin();
    auto const end   = csv_input.end();

    qi::phrase_parse(
      begin, end,
      csv_grammar_t<iter_t>{},
      qi::space,
      csv_rows);

    REQUIRE(csv_rows.size() == 8);

    auto const rtree = csv_rows_to_rtree(csv_rows);

    REQUIRE(rtree.size() == csv_rows.size());

    for (auto const& pt_csv_row_pair : rtree) {
      std::cout << pt_csv_row_pair.first << "\n";
    }
  }
}