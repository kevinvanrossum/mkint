#include "kmint/util/wrapped_iterator.hpp"
#include "gtest/gtest.h"
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

using kmint::util::wrap_iterator;
using kmint::util::wrapped_iterator;

namespace {
int &deref_unique_ptr(std::unique_ptr<int> const &ptr) { return *ptr; }

class WrappedRandomAccessIt : public testing::Test {
protected:
  std::vector<std::unique_ptr<int>> v{};
  void SetUp() override {
    v.emplace_back(new int{1});
    v.emplace_back(new int{2});
  }
};

TEST_F(WrappedRandomAccessIt, GetsObjectsOut) {
  EXPECT_EQ(1, *wrap_iterator<int>(std::begin(v), deref_unique_ptr));
}

TEST_F(WrappedRandomAccessIt, Updates) {
  auto i = wrap_iterator<int>(std::begin(v), deref_unique_ptr);
  *i = 9;
  EXPECT_EQ(9, *v[0]);
}

TEST_F(WrappedRandomAccessIt, GoesToNext) {
  auto i = wrap_iterator<int>(std::begin(v), deref_unique_ptr);
  ++i;
  EXPECT_EQ(2, *i);
}

TEST_F(WrappedRandomAccessIt, GoesToPrevious) {
  auto i = wrap_iterator<int>(std::end(v), deref_unique_ptr);
  --i;
  EXPECT_EQ(2, *i);
}

TEST_F(WrappedRandomAccessIt, IsCopyAssignable) {
  auto i = wrap_iterator<int>(std::end(v), deref_unique_ptr);
  EXPECT_TRUE(std::is_copy_assignable<decltype(i)>::value);
}

TEST_F(WrappedRandomAccessIt, CanModifyViaArrowOperator) {
  struct mystruct {
    int i{};
  };
  std::vector<std::unique_ptr<mystruct>> v{};
  v.emplace_back(new mystruct{1});
  v.emplace_back(new mystruct{2});
  auto it = wrap_iterator<mystruct>(std::begin(v),
                                    [](auto &i) -> mystruct & { return *i; });
  it->i = 3;
  EXPECT_EQ(3, v[0]->i);
}

} // namespace
