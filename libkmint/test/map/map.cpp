#include "kmint/map/map.hpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <sstream>

namespace {
using namespace kmint::map;

const char *map_data = R"map(2 3 2
X 1 1 0
Y 1 2 0
Z 0 0 0

XY
YZ
ZZ
)map";

TEST(Map, ShouldBuildGraph) {
  std::istringstream is{map_data};
  auto m = read_map(is);
  EXPECT_EQ(4, m.size().width());
  EXPECT_EQ(6, m.size().height());
  auto &g = m.graph();
  EXPECT_EQ(3, g.num_nodes());
  EXPECT_EQ(1, std::count_if(g.begin(), g.end(), [](auto const &n) {
              return n.node_info().kind == 'X';
            }));
  EXPECT_EQ(2, std::count_if(g.begin(), g.end(), [](auto const &n) {
              return n.node_info().kind == 'Y';
            }));
}

} // namespace
