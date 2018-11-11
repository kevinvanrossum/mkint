#include "kmint/math/size.hpp"
#include "gtest/gtest.h"
#include <sstream>

namespace {
using kmint::math::isize;

TEST(ISize, ShouldOutput) {
  isize s{1, 2};
  std::ostringstream os{};
  os << s;
  EXPECT_EQ("1 2", os.str());
}

TEST(ISize, ShouldInput) {
  isize s{};
  std::istringstream is{"1 2"};
  is >> s;
  EXPECT_EQ(1, s.width());
  EXPECT_EQ(2, s.height());
}

} // namespace
