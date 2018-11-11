#ifndef KMINT_MATH_SIZE_HPP
#define KMINT_MATH_SIZE_HPP

#include "kmint/primitives.hpp"
#include <istream>
#include <ostream>

namespace kmint::math {

template <typename T> class basic_size {
public:
  constexpr basic_size() noexcept = default;
  constexpr basic_size(T width, T height) noexcept
      : width_{width}, height_{height} {}
  constexpr T width() const noexcept { return width_; }
  constexpr T height() const noexcept { return height_; }
  constexpr void width(T new_width) noexcept { width_ = new_width; }
  constexpr void height(T new_height) noexcept { height_ = new_height; }
  constexpr basic_size &operator*=(T x) {
    width(width()*x);
    height(height()*x);
    return *this;
  }

private:
  T width_{};
  T height_{};
};

using size = basic_size<scalar>;
using isize = basic_size<int>;

  /*! \brief Multiplies a size by a scalar.

    This multiplies both width and height by the same factor

    \param sz the size to multiply
    \param x the scalar to multiply with
  */
template<typename T>
basic_size<T> operator*(basic_size<T> sz, T x) {
  return { sz.width() * x, sz.height() * x };
}
  /*! \brief Multiplies a size by a scalar.

    This multiplies both width and height by the same factor

    \param x the scalar to multiply with
    \param sz the size to multiply
  */
template<typename T>
basic_size<T> operator*(T x, basic_size<T> sz) {
  // use the operator defined above
  return sz * x;
}

template <typename T>
std::istream &operator>>(std::istream &is, basic_size<T> &bs) {
  if (T w, h; is >> w >> h) {
    bs.width(w);
    bs.height(h);
  }
  return is;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, basic_size<T> bs) {
  return os << bs.width() << ' ' << bs.height();
}
} // namespace kmint::math

#endif /* KMINT_MATH_SIZE_HPP */
