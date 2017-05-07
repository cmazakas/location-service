#ifndef CSV_GRAMMAR_HPP_
#define CSV_GRAMMAR_HPP_

#include <boost/spirit/include/qi.hpp>
#include "csv_row_t.hpp"

namespace qi = boost::spirit::qi;

template <typename Iterator>
using rule_t = qi::rule<Iterator, csv_rows_t(), qi::space_type>;

template <typename Iterator>
struct csv_grammar_t : qi::grammar<Iterator, csv_rows_t(), qi::space_type>
{
  using string_rule_t = qi::rule<Iterator, std::string(), qi::space_type>; 
  using dbl_rule_t    = qi::rule<Iterator, double(),      qi::space_type>;
  using int_rule_t    = qi::rule<Iterator, int(),         qi::space_type>;

  rule_t<Iterator> start;

  string_rule_t zip;
  string_rule_t city;
  string_rule_t state;

  dbl_rule_t latitude;
  dbl_rule_t longitude;

  int_rule_t timezone;
  int_rule_t dst;

  csv_grammar_t(void) : csv_grammar_t::base_type{start}
  {
    zip   = *(qi::alnum);
    city  = *(~qi::char_('"'));
    state = *(~qi::char_('"'));

    latitude  = qi::double_;
    longitude = qi::double_;

    timezone  = qi::int_;
    dst       = qi::int_;

    start = 
      -(
        qi::lit("\"zip\"")       >> ',' >> "\"city\""      >> ',' >> "\"state\""
        >> ',' >> "\"latitude\"" >> ',' >> "\"longitude\"" >> ',' >> "\"timezone\"" 
        >> ',' >> "\"dst\"")
      >> *(
        '"' >> zip       >> '"' >> ',' >>
        '"' >> city      >> '"' >> ',' >>
        '"' >> state     >> '"' >> ',' >>
        '"' >> latitude  >> '"' >> ',' >>
        '"' >> longitude >> '"' >> ',' >>
        '"' >> timezone  >> '"' >> ',' >>
        '"' >> dst       >> '"');
  }
};

#endif // CSV_GRAMMAR_HPP_