#ifndef KMINT_MATH_ANGLE_HPP
#define KMINT_MATH_ANGLE_HPP

#include "kmint/primitives.hpp"
#include <cmath>

namespace kmint {
namespace math {

constexpr scalar pi = static_cast<scalar>(3.14159265358979323846);

class angle {
  scalar value_;
  constexpr explicit angle(scalar value) noexcept : value_{value} {}

public:
  constexpr scalar radians() const noexcept { return value_; }
  constexpr scalar degrees() const noexcept {
    return static_cast<scalar>(value_ * 180.0 / pi);
  }
  constexpr angle &operator+=(angle other) noexcept {
    value_ += other.value_;
    return *this;
  }
  constexpr angle &operator-=(angle other) noexcept {
    value_ += other.value_;
    return *this;
  }
  constexpr angle &operator*=(scalar x) noexcept {
    value_ *= x;
    return *this;
  }
  constexpr angle &operator/=(scalar x) noexcept {
    value_ *= x;
    return *this;
  }
  constexpr angle &operator-() noexcept {
    value_ *= -1.0;
    return *this;
  }
  friend constexpr angle operator"" _rad(
      long double r) noexcept; // needs to be
                               // a friend to call private constructor

  friend constexpr angle operator"" _deg(long double d) noexcept; // needs to be
                                                                  // a friend to
                                                                  // call
                                                                  // private
                                                                  // constructor

  friend constexpr angle operator+(angle a, angle b) noexcept { return a += b; }
  friend constexpr angle operator-(angle a, angle b) noexcept { return a -= b; }
  friend constexpr angle operator*(angle a, scalar b) noexcept {
    return a *= b;
  }

  friend constexpr angle operator*(scalar a, angle b) noexcept { return b * a; }

  friend constexpr angle operator/(angle a, scalar b) noexcept {
    return a /= b;
  }

  friend constexpr angle operator/(scalar a, angle b) noexcept { return b / a; }

  friend angle acos(scalar c);
  friend angle asin(scalar c);
  friend angle atan(scalar c);
  friend angle atan2(scalar y, scalar x);
};

constexpr angle operator"" _rad(long double r) noexcept {
  return angle{static_cast<scalar>(r)};
}

constexpr angle operator"" _deg(long double d) noexcept {
  return angle{static_cast<scalar>(d * pi / 180.0)};
}

angle acos(scalar c);
angle atan(scalar c);
angle atan2(scalar y, scalar x);
angle asin(scalar c);

} // namespace math
} // namespace kmint
#endif // KMINT_MATH_ANGLE_HPP
