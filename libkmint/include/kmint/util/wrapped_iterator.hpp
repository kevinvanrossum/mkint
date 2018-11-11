#ifndef KMINT_UTIL_WRAPPED_ITERATOR_HPP
#define KMINT_UTIL_WRAPPED_ITERATOR_HPP

#include <functional>
#include <iterator>
#include <type_traits>

namespace kmint {
namespace util {

template <typename It>
using category_tag_t = typename std::iterator_traits<It>::iterator_category;

template <typename It>
using difference_type_t = typename std::iterator_traits<It>::difference_type;

template <typename It>
inline constexpr bool is_bidirectional_iterator =
    std::is_same<category_tag_t<It>, std::bidirectional_iterator_tag>::value ||
    std::is_same<category_tag_t<It>, std::random_access_iterator_tag>::value;

template <typename It>
inline constexpr bool is_random_access_iterator =
    std::is_same<category_tag_t<It>, std::random_access_iterator_tag>::value;

template <typename U, typename T, typename V = void>
using if_same_t = std::enable_if_t<std::is_same<U, T>::value, V>;

template <typename It>
using reference_t = typename std::iterator_traits<It>::reference;

template <typename It, typename V = void>
using if_bidirectional_t = std::enable_if_t<is_bidirectional_iterator<It>, V>;

template <typename It, typename V = void>
using if_random_access_t = std::enable_if_t<is_random_access_iterator<It>, V>;

template <typename T, typename It>
class wrapped_iterator
    : public std::iterator<category_tag_t<It>, T, difference_type_t<It>> {
public:
  wrapped_iterator(It it, std::function<T &(reference_t<It>)> deref)
      : it_{it}, deref_{std::move(deref)} {}

  wrapped_iterator &operator++() {
    ++it_;
    return *this;
  }

  wrapped_iterator operator++(int) {
    auto old = *this;
    ++(*this);
    return old;
  }

  template <typename Dummy = wrapped_iterator>
  if_bidirectional_t<It, Dummy> &operator--() {
    --it_;
    return *this;
  }

  template <typename Dummy = wrapped_iterator>
  if_bidirectional_t<It, Dummy> operator--(int) {
    auto old = *this;
    --(*this);
    return *this;
  }

  template <typename Dummy = wrapped_iterator>
  if_random_access_t<It, Dummy> &operator+=(difference_type_t<It> v) {
    it_ += v;
    return *this;
  }

  template <typename Dummy = wrapped_iterator>
  if_random_access_t<It, Dummy> &operator-=(difference_type_t<It> v) {
    it_ -= v;
    return *this;
  }

  template <typename Dummy = wrapped_iterator>
  if_random_access_t<It, Dummy> operator+(difference_type_t<It> rhs) const {
    auto old = *this;
    old += rhs;
    return old;
  }

  template <typename Dummy = wrapped_iterator>
  if_random_access_t<It, Dummy> operator-(difference_type_t<It> rhs) const {
    auto old = *this;
    old -= rhs;
    return old;
  }

  template <typename Dummy = difference_type_t<It>>
  if_random_access_t<It, Dummy> operator-(wrapped_iterator rhs) const {
    return it_ - rhs.it_;
  }

  T const &operator*() const { return deref_(*it_); }
  T &operator*() { return deref_(*it_); }
  T *operator->() { return &deref_(*it_); }
  T const *operator->() const { return &deref_(*it_); }
  decltype(auto) operator[](difference_type_t<It> i) { return deref_(it_ + i); }
  decltype(auto) operator<(wrapped_iterator rhs) const { return it_ < rhs.it_; }
  decltype(auto) operator<=(wrapped_iterator rhs) const {
    return it_ <= rhs.it_;
  }
  decltype(auto) operator>(wrapped_iterator rhs) const { return it_ > rhs.it_; }
  decltype(auto) operator>=(wrapped_iterator rhs) const {
    return it_ >= rhs.it_;
  }
  decltype(auto) operator==(wrapped_iterator rhs) const {
    return it_ == rhs.it_;
  }
  decltype(auto) operator!=(wrapped_iterator rhs) const {
    return it_ != rhs.it_;
  }

private:
  It it_;
  std::function<T &(reference_t<It>)> deref_;
}; // namespace util

template <typename T, typename It, typename DerefFun>
wrapped_iterator<T, It> wrap_iterator(It it, DerefFun &&deref) {
  return {it, std::forward<DerefFun>(deref)};
}

} // namespace util
} // namespace kmint
#endif
