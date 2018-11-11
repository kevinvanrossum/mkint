#include "kmint/math/vector2d.hpp"
#include <istream>
#include <ostream>

namespace kmint {
namespace math {

std::istream &operator>>(std::istream &is, vector2d &p) {
  scalar x, y;
  if (is >> x && is >> y) {
    p.x(x);
    p.y(y);
  }
  return is;
}

std::ostream &operator<<(std::ostream &os, vector2d p) {
  os << p.x() << " " << p.y();
  return os;
}
} // namespace math
} // namespace kmint
