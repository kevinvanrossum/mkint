#include "kmint/math/angle.hpp"

namespace kmint {
namespace math {
angle acos(scalar c) { return angle{std::acos(c)}; }
angle asin(scalar c) { return angle{std::asin(c)}; }
angle atan(scalar c) { return angle{std::atan(c)}; }
angle atan2(scalar y, scalar x) { return angle{std::atan2(y, x)}; }
} // namespace math
} // namespace kmint
