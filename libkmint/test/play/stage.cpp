#include "kmint/play/stage.hpp"
#include "kmint/play/actor.hpp"
#include "kmint/ui/noop_drawable.hpp"
#include "gtest/gtest.h"
#include <string>

namespace {
using kmint::play::stage;

TEST(Stage, ShouldConstruct) {
  stage s{};
  EXPECT_EQ(true, s.begin() == s.end());
}

class silly_actor : public kmint::play::actor {
public:
  silly_actor(int i, std::string s)
      : test_int_{i}, test_string_{std::move(s)} {}
  kmint::ui::drawable const &drawable() const override { return drawable_; }
  kmint::math::vector2d location() const override { return {0.f, 0.f}; }
  int test_int() const noexcept { return test_int_; }
  std::string const &test_string() const noexcept { return test_string_; }
  bool act_called() const noexcept { return act_called_; }
  void act(kmint::delta_time /*dt*/) override { act_called_ = true; }

private:
  kmint::ui::noop_drawable drawable_{};
  bool act_called_{false};
  int test_int_;
  std::string test_string_;
};

TEST(Stage, ItShouldAddActor) {
  stage s{};
  auto &sa = s.build_actor<silly_actor>(10, "HELLO");
  EXPECT_EQ(&sa, &(*s.begin()));
  EXPECT_EQ(10, sa.test_int());
  EXPECT_EQ("HELLO", sa.test_string());
}

TEST(Stage, ItShouldRemoveActor) {
  stage s{};
  auto &sa = s.build_actor<silly_actor>(10, "HELLO");
  EXPECT_FALSE(s.cbegin() == s.cend()); // non empty stage
  s.remove_actor(sa);
  EXPECT_TRUE(s.cbegin() == s.cend()); // empty stage
}

TEST(Stage, ItShouldCallUpdate) {
  stage s{};
  auto &sa = s.build_actor<silly_actor>(10, "HELLO");
  s.act(kmint::from_seconds(1.0));
  EXPECT_TRUE(sa.act_called());
}

} // namespace
