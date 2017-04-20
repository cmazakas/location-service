#ifndef CSV_GRAMMAR_HPP_
#define CSV_GRAMMAR_HPP_

#include <vector>
#include <boost/spirit/include/qi.hpp>
#include "csv_row_t.hpp"

namespace qi = boost::spirit::qi;

using result_t = std::vector<csv_row_t>;

template <typename Iterator>
using rule_t = qi::rule<Iterator, result_t(), qi::space_type>;

template <typename Iterator>
struct csv_grammar_t : qi::grammar<Iterator, result_t(), qi::space_type>
{
  using iter_t = Iterator;

  using string_rule_t = qi::rule<iter_t, std::string(), qi::space_type>; 
  using dbl_rule_t    = qi::rule<iter_t, double(), qi::space_type>;
  using int_rule_t    = qi::rule<iter_t, int(), qi::space_type>;

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

    start = *(
      '"' >> zip >> '"' >> ',' >>
      '"' >> city >> '"' >> ',' >>
      '"' >> state >> '"' >> ',' >>
      '"' >> latitude >> '"' >> ',' >>
      '"' >> longitude >> '"' >> ',' >>
      '"' >> timezone >> '"' >> ',' >>
      '"' >> dst >> '"');
  }

   
};

#endif // CSV_GRAMMAR_HPP_