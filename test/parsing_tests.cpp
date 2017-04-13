#include <catch.hpp>

#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <string>

#include <boost/tuple/tuple.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/fusion/adapted.hpp>

namespace spirit = boost::spirit;
namespace qi     = spirit::qi;

TEST_CASE("Parsing tests")
{
  SECTION("Spirit presentation")
  {
    std::string const input{
      "foo : bar ,"
      "gorp : smart ,"
      "falcou : \"crazy frenchman\""
    };

    using iter_t       = decltype(input.begin());
    using space_rule_t = qi::rule<iter_t, std::string(), qi::space_type>;
    using kvp_rule_t   = qi::rule<iter_t, std::pair<std::string, std::string>(), qi::space_type>;

    auto const name     = space_rule_t{qi::alpha >> *qi::alnum};
    auto const quote    = space_rule_t{'"' >> qi::lexeme[*(~qi::char_('"'))] >> '"'};
    auto const kvp_item = kvp_rule_t{name >> ':' >> (quote | name)};

    auto kvp_table = std::map<std::string, std::string>{};

    qi::phrase_parse(
      input.begin(), input.end(),
      kvp_item % ',',
      qi::space,
      kvp_table);

    for (auto const& kvp : kvp_table) {
      std::cout << std::get<0>(kvp) << ',' << std::get<1>(kvp) << '\n';
    }
  }

  SECTION("First binary op!")
  {
    std::string input{"12 - 8"};

    using iter_t = decltype(input.begin());

    using arithmetic_rule = qi::rule<iter_t, int(int), qi::space_type>;
    using binary_op_rule  = qi::rule<iter_t, int, spirit::locals<int>, qi::space_type>;

    arithmetic_rule add;
    arithmetic_rule mult;
    arithmetic_rule sub;
    arithmetic_rule div;

    binary_op_rule binary_op;

    add  = '+' >> qi::int_[qi::_val = qi::_r1 + qi::_1];
    mult = '*' >> qi::int_[qi::_val = qi::_r1 * qi::_1];
    sub  = '-' >> qi::int_[qi::_val = qi::_r1 - qi::_1];
    div  = '/' >> qi::int_[qi::_val = qi::_r1 / qi::_1];

    binary_op = qi::int_[qi::_a = qi::_1] >> (
      add(qi::_a) 
      | mult(qi::_a) 
      | sub(qi::_a) 
      | div(qi::_a))[qi::_val = qi::_1];

    int result = -1;

    qi::phrase_parse(
      input.begin(), input.end(),
      binary_op, qi::space, result);

    REQUIRE(result == 4);
  }

  SECTION("Sample CSV line")
  {
    std::string const input{
      "\"00210\",\"Portsmouth\",\"NH\",\"43.005895\",\"-71.013202\",\"-5\",\"1\""};

    using iter_t = decltype(input.begin());

    using string_rule_t = qi::rule<iter_t, std::string(), qi::space_type>; 
    using dbl_rule_t    = qi::rule<iter_t, double(), qi::space_type>;
    using int_rule_t    = qi::rule<iter_t, int(), qi::space_type>;

    using csv_value_t = boost::tuple<
      std::string,
      std::string,
      std::string,
      double,
      double,
      int,
      int>;

    using csv_rule_t = qi::rule<iter_t, csv_value_t(), qi::space_type>;

    auto const zip       = string_rule_t{*(qi::alnum)};
    auto const city      = string_rule_t{*(~qi::char_('"'))};
    auto const state     = string_rule_t{*(~qi::char_('"'))};

    auto const latitude  = dbl_rule_t{qi::double_};
    auto const longitude = dbl_rule_t{qi::double_};

    auto const timezone  = int_rule_t{qi::int_};
    auto const dst       = int_rule_t{qi::int_};

    auto const csv_row = csv_rule_t{
      '"' >> zip       >> '"' >> ',' >>
      '"' >> city      >> '"' >> ',' >>
      '"' >> state     >> '"' >> ',' >>
      '"' >> latitude  >> '"' >> ',' >>
      '"' >> longitude >> '"' >> ',' >>
      '"' >> timezone  >> '"' >> ',' >>
      '"' >> dst       >> '"'};

    csv_value_t csv_row_result;

    qi::phrase_parse(
      input.begin(), input.end(),
      csv_row,
      qi::space,
      csv_row_result);

    std::cout 
      << boost::get<0>(csv_row_result) << ", "
      << boost::get<1>(csv_row_result) << ", "
      << boost::get<2>(csv_row_result) << ", "

      << boost::get<3>(csv_row_result) << ", "
      << boost::get<4>(csv_row_result) << ", "

      << boost::get<5>(csv_row_result) << ", "
      << boost::get<6>(csv_row_result) << ", "

      << '\n';
  }
}