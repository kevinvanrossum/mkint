#include "kmint/ui/events/event.hpp"
#include "gtest/gtest.h"

namespace {
using namespace kmint::ui::events;

TEST(Modifier, DefaultIsNone) {
  modifier m{};
  EXPECT_FALSE(any_modifier(m));
}

TEST(Modifier, CanBeCombined) {
  auto combined = modifier::ctrl | modifier::shift;
  EXPECT_TRUE(includes_modifier(combined, modifier::ctrl));
  EXPECT_TRUE(includes_modifier(combined, modifier::shift));
}

TEST(Modifier, CanBeChecked) {
  auto combined = modifier::ctrl & modifier::shift;
  EXPECT_FALSE(any_modifier(combined));
  combined = modifier::ctrl & modifier::ctrl;
  EXPECT_TRUE(any_modifier(combined));
  EXPECT_TRUE(includes_modifier(combined, modifier::ctrl));
}


} // namespace
