#ifndef KMINT_MATH_MATRIX_HPP
#define KMINT_MATH_MATRIX_HPP
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <ostream>
#include <type_traits>
#include <vector>
namespace kmint::math {
template <typename T> class matrix {
public:
  matrix(std::size_t rows, std::size_t cols, T const &init = T{})
      : rows_{rows}, cols_{cols}, values_(rows * cols, init) {}
  T &operator()(std::size_t row, std::size_t col) { return get(row, col); }
  T &get(std::size_t row, std::size_t col) {
    return values_[row * cols_ + col];
  }
  T const &operator()(std::size_t row, std::size_t col) const {
    return get(row, col);
  }
  T const &get(std::size_t row, std::size_t col) const {
    return values_[row * cols_ + col];
  }
  template <typename U> matrix &operator+=(matrix<U> const &m) {
    assert(m.n_rows() == n_rows() && m.n_cols() == n_cols());
    for (std::size_t r = 0; r < n_rows(); ++r) {
      for (std::size_t c = 0; c < n_cols(); ++c) {
        get(r, c) += m.get(r, c);
      }
    }
    return *this;
  }

  template <typename U> matrix &operator-=(matrix<U> const &m) {
    assert(m.n_rows() == n_rows() && m.n_cols() == n_cols());
    for (std::size_t r = 0; r < n_rows(); ++r) {
      for (std::size_t c = 0; c < n_cols(); ++c) {
        get(r, c) -= m.get(r, c);
      }
    }
    return *this;
  }
  matrix &operator*=(T const &val) {
    std::for_each(std::begin(values_), std::end(values_),
                  [&val](auto &v) { v *= val; });
    return *this;
  }
  matrix &operator/=(T const &val) {
    std::for_each(std::begin(values_), std::end(values_),
                  [&val](auto &v) { v /= val; });
    return *this;
  }
  std::size_t n_rows() const noexcept { return rows_; }
  std::size_t n_cols() const noexcept { return cols_; }

private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<T> values_;
};

template <typename T>
std::ostream &operator<<(std::ostream &os, matrix<T> const &m) {
  for (std::size_t r = 0; r < m.n_rows(); ++r) {
    for (std::size_t c = 0; c < m.n_cols(); ++c) {
      os << m(r, c) << ", ";
    }
    os << '\n';
  }
  return os;
}

} // namespace kmint::math
#endif
