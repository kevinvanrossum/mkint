#ifndef KMINT_MATH_VECTOR2D_HPP
#define KMINT_MATH_VECTOR2D_HPP

#include "kmint/primitives.hpp"
#include <cmath>
#include <iosfwd>

namespace kmint {
namespace math {

template <typename Scalar> class basic_vector2d {
public:
  basic_vector2d() noexcept = default;
  basic_vector2d(Scalar x, Scalar y) noexcept : x_{x}, y_{y} {}
  Scalar x() const noexcept { return x_; }
  void x(Scalar newX) noexcept { x_ = newX; }
  Scalar y() const noexcept { return y_; }
  void y(Scalar newY) noexcept { y_ = newY; }

  constexpr basic_vector2d &operator+=(basic_vector2d other) noexcept {
    x_ += other.x_;
    y_ += other.y_;
    return *this;
  }

  constexpr basic_vector2d &operator-=(basic_vector2d other) noexcept {
    x_ -= other.x_;
    y_ -= other.y_;
    return *this;
  }

  constexpr basic_vector2d &operator*=(Scalar s) noexcept {
    x_ *= s;
    y_ *= s;
    return *this;
  }

  constexpr basic_vector2d &operator/=(Scalar s) noexcept {
    x_ /= s;
    y_ /= s;
    return *this;
  }

private:
  Scalar x_{};
  Scalar y_{};
};

using vector2d = basic_vector2d<scalar>;
using ivector2d = basic_vector2d<int>;

template <typename Scalar>
std::istream &operator>>(std::istream &is, basic_vector2d<Scalar> &p) {
  Scalar x, y;
  if (is >> x && is >> y) {
    p.x(x);
    p.y(y);
  }
  return is;
}

template <typename Scalar>
std::ostream &operator<<(std::ostream &os, basic_vector2d<Scalar> p) {
  os << p.x() << " " << p.y();
  return os;
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> perp(basic_vector2d<Scalar> v) {
  return {-v.y(), v.x()};
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator-(basic_vector2d<Scalar> a,
                                           basic_vector2d<Scalar> b) {
  return {a.x() - b.x(), a.y() - b.y()};
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator+(basic_vector2d<Scalar> a,
                                           basic_vector2d<Scalar> b) {
  return {a.x() + b.x(), a.y() + b.y()};
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator*(basic_vector2d<Scalar> v, scalar s) {
  return v *= s;
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator*(scalar s, basic_vector2d<Scalar> v) {
  return operator*(v, s);
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator/(basic_vector2d<Scalar> v, scalar s) {
  return v /= s;
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> operator/(scalar s, basic_vector2d<Scalar> v) {
  return operator/(v, s);
}

template <typename Scalar>
constexpr scalar dot(basic_vector2d<Scalar> a, basic_vector2d<Scalar> b) {
  return a.x() * b.x() + a.y() * b.y();
}

template <typename Scalar> constexpr auto norm2(basic_vector2d<Scalar> p) {
  return dot(p, p);
}

template <typename Scalar> constexpr auto norm(basic_vector2d<Scalar> p) {
  return std::sqrt(dot(p, p));
}

template <typename Scalar>
constexpr basic_vector2d<Scalar> normalize(basic_vector2d<Scalar> p) {
  auto ls = norm(p);
  return {p.x() / ls, p.y() / ls};
}

template <typename Scalar>
constexpr auto distance(basic_vector2d<Scalar> from,
                        basic_vector2d<Scalar> to) {
  return norm(from - to);
}

template <typename Scalar>
constexpr auto distance2(basic_vector2d<Scalar> from,
                         basic_vector2d<Scalar> to) {
  return norm2(from - to);
}
} // namespace math
} // namespace kmint

#endif // KMINT_MATH_VECTOR2D_HPP
