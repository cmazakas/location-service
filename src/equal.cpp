#include <cmath>
#include <limits>

#include "equal.hpp"



auto eq(float const  a, float const  b) -> bool
{
  return std::abs(a - b) < (std::abs(a + b) * std::numeric_limits<float>::epsilon());
}

auto eq(double const a, double const b) -> bool
{
  return std::abs(a - b) < (std::abs(a + b) * std::numeric_limits<double>::epsilon() * 5);
}