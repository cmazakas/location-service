#include "point_t.hpp"

auto operator<<(std::ostream& os, point_t const& p) -> std::ostream&
{
  os << "{ " << p.get<0>() << ", " << p.get<1>() << ", " << p.get<2>() << " }";
  return os;
}