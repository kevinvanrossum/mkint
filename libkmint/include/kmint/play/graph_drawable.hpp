#ifndef KMINT_PLAY_GRAPH_RENDERABLE_HPP
#define KMINT_PLAY_GRAPH_RENDERABLE_HPP

#include "kmint/graphics/color.hpp"
#include "kmint/graphics/image.hpp"
#include "kmint/math/size.hpp"
#include "kmint/ui/drawable.hpp"
#include "kmint/ui/window.hpp"

namespace kmint::play {

class actor;

template <typename Graph> class graph_drawable : public ui::drawable {
public:
  graph_drawable(Graph const &g) : ui::drawable{}, graph_{&g} {}
  void draw(ui::frame &f) const override {
    // draw edges
    f.render_color(edge_color);
    for (auto const &node : *graph_) {
      for (auto const &edge : node) {
        // TODO: Add weights as soon as frame supports it
        f.draw_line(edge.from().location(),
                    edge.to().location() /*, edge.weight()*/);
      }
    }
    // draw nodes
    f.render_color(node_color);
    for (auto const &node : *graph_) {
      f.draw_rectangle(node.location(), node_size,
                       node.tagged() ? tagged_node_color : node_color);
    }
  }

private:
  static constexpr math::size node_size = {5.0f, 5.0f};
  static constexpr graphics::color node_color = {255, 0, 0};
  static constexpr graphics::color tagged_node_color = {0, 255, 255};
  static constexpr graphics::color edge_color = {255, 255, 255};
  Graph const *graph_;
};
} // namespace kmint::play

#endif /* KMINT_PLAY_GRAPH_RENDERABLE_HPP */
