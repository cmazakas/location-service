#include <catch.hpp>
#include <string>

#include "csv_grammar.hpp"

TEST_CASE("The csv parsing grammar")
{
  auto const input = std::string{"qawawseraer"};

  using iter_t = decltype(input.begin());

  csv_grammar_t<iter_t> csv_grammar;
}