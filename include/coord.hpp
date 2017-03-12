#ifndef COORD_HPP_
#define COORD_HPP_

#include <boost/serialization/strong_typedef.hpp>

BOOST_STRONG_TYPEDEF(float, longitude_t)
BOOST_STRONG_TYPEDEF(float, latitude_t)

struct coord_t
{
	longitude_t longitude;
	latitude_t  latitude;
};

#endif // COORD_HPP_