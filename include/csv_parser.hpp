#ifndef CSV_PARSER_HPP_
#define CSV_PARSER_HPP_

#include <string>
#include "csv_grammar.hpp"

auto get_csv_location_data(std::string const& filepath) -> csv_rows_t;

#endif // CSV_PARSER_HPP_
