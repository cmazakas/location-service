#include <fstream>
#include <boost/spirit/include/qi.hpp>

#include "csv_parser.hpp"
#include "csv_grammar.hpp"

auto get_csv_location_data(std::string const& filepath) -> csv_rows_t
{
  namespace qi = boost::spirit::qi;
  using iter_t = boost::spirit::istream_iterator;

  std::ifstream ifs{filepath};
  ifs >> std::noskipws;

  if (!ifs.is_open()) {
    return {};
  }

  auto const begin = iter_t{ifs};
  auto const end   = iter_t{};

  size_t const estimated_row_num = 64000;
  csv_rows_t csv_rows;
  csv_rows.reserve(estimated_row_num);

  qi::phrase_parse(
    begin, end,
    csv_grammar_t<iter_t>{},
    qi::space,
    csv_rows);

  return csv_rows;
}