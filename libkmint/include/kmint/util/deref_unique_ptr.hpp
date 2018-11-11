#ifndef KMINT_UTIL_DEREF_UNIQUE_PTR_HPP
#define KMINT_UTIL_DEREF_UNIQUE_PTR_HPP

#include <memory>

namespace kmint {
namespace util {

template <typename T> T &deref_unique_ptr(std::unique_ptr<T> const &ptr) {
  return *ptr;
}

template <typename T>
T const &deref_unique_ptr_const(std::unique_ptr<T> const &ptr) {
  return *ptr;
}

} // namespace util
} // namespace kmint

#endif /* KMINT_UTIL_DEREF_UNIQUE_PTR_HPP */
