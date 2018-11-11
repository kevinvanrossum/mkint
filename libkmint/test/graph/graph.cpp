#include "kmint/graph/graph.hpp"
#include "gtest/gtest.h"
#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>

namespace {
using kmint::graph::graph;

TEST(Graph, ShouldConstruct) { kmint::graph::graph g{}; }

TEST(Graph, ItShouldAddNode) {
  graph g{};
  auto &n = g.add_node(kmint::math::vector2d{});
  auto &f = *g.begin();
  EXPECT_EQ(&n, &f);
}
TEST(Graph, ItShouldAllowToIterateOverNodes) {
  graph g{};
  auto const &r = g;
  auto &n = g.add_node(kmint::math::vector2d{});
  auto const &f = *r.begin();
  EXPECT_EQ(&n, &f);
}

TEST(Graph, ItShouldTagNodes) {
  graph g{};
  g.add_node(kmint::math::vector2d{});
  g.add_node(kmint::math::vector2d{});
  g.tag(g.begin(), g.end());
  EXPECT_EQ(true, std::accumulate(g.begin(), g.end(), true,
                                  [](bool tot, auto const &n) {
                                    return tot && n.tagged();
                                  }));
}

TEST(Graph, ItShouldUntagNodes) {
  graph g{};
  g.add_node(kmint::math::vector2d{}).tagged(true);
  g.add_node(kmint::math::vector2d{}).tagged(true);
  g.untag_all();
  EXPECT_EQ(false, std::accumulate(g.begin(), g.end(), false,
                                   [](bool tot, auto const &n) {
                                     return tot || n.tagged();
                                   }));
}

TEST(Graph, ItShouldReadFromIStream) {
  std::istringstream is{
      R"graph(100 100
200 200

0 1 1
1 0 2
)graph"};
  graph g{kmint::graph::read_graph(is)};
  EXPECT_EQ(2, g.num_nodes());
  EXPECT_EQ(true, std::accumulate(g.begin(), g.end(), true,
                                  [](bool tot, auto const &n) {
                                    return tot && (n.num_edges() == 1);
                                  }));
  // test edges

  EXPECT_EQ(&g[0], &g[0][0].from());
  EXPECT_EQ(&g[1], &g[0][0].to());
  EXPECT_FLOAT_EQ(1, g[0][0].weight());

  EXPECT_EQ(&g[0], &g[1][0].to());
  EXPECT_EQ(&g[1], &g[1][0].from());
  EXPECT_FLOAT_EQ(2, g[1][0].weight());
}

struct simple_node_info {
  char c;
};
std::istream &operator>>(std::istream &is, simple_node_info &ni) {
  char c;
  if (is >> c)
    ni.c = c;
  return is;
}

TEST(Graph, ItShouldReadNodeInfo) {
  std::istringstream is{
      R"graph(100 100 a
200 200 b
)graph"};
  auto g = kmint::graph::read_basic_graph<simple_node_info>(is);
  EXPECT_EQ('a', g[0].node_info().c);
  EXPECT_EQ('b', g[1].node_info().c);
}

} // namespace
