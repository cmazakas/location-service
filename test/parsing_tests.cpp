#include <catch.hpp>

#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <tuple>

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
}