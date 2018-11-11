#ifndef KMINT_UTIL_ITERATOR_WRAPPER_HPP
#define KMINT_UTIL_ITERATOR_WRAPPER_HPP

#include <iterator>

namespace kmint {
namespace util {

template <typename It>
using category_tag_t = typename std::iterator_traits<It>::iteratory_category;

template <typename It>
using difference_type_t = typename std::iterator_traits<It>::difference_type;

template <typename T, typename It>
class iterator_wrapper
    : public std::iterator<category_tag_t<It>, T, difference_type_t<It>> {};

} // namespace util
} // namespace kmint
#endif
