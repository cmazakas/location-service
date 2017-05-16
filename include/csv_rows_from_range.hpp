#ifndef CSV_ROWS_FROM_RANGE_HPP_
#define CSV_ROWS_FROM_RANGE_HPP_

#include "csv_row_t.hpp"
#include "csv_grammar.hpp"

template <typename InputIterator>
auto csv_rows_from_range(InputIterator begin, InputIterator end) -> csv_rows_t
{
  namespace qi = boost::spirit::qi;

  auto csv_rows = csv_rows_t{};

  qi::phrase_parse(
    begin, end,
    csv_grammar_t<InputIterator>{},
    qi::space,
    csv_rows);

  return csv_rows;
}

#endif // CSV_ROWS_FROM_RANGE_HPP_
