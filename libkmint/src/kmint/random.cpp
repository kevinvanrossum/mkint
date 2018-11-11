#include "kmint/random.hpp"
#include <cassert>
#include <random>

namespace {
std::default_random_engine &random_engine() {
  static std::random_device rd{};
  static std::default_random_engine re{rd()};
  return re;
}
} // namespace

namespace kmint {
int random_int(int low, int high) {
  assert(high > low);
  std::uniform_int_distribution<int> d{low, high - 1};
  return d(random_engine());
}
scalar random_scalar(scalar low, scalar high) {
  std::uniform_real_distribution<scalar> d{low, high};
  return d(random_engine());
}
} // namespace kmint
