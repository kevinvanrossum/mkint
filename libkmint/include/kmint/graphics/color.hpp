#ifndef KMINT_GRAPHICS_COLOR_HPP
#define KMINT_GRAPHICS_COLOR_HPP

#include "kmint/primitives.hpp"
#include <cstdint>

namespace kmint {
namespace graphics {

using color_component = std::uint8_t;
constexpr color_component to_color_component(scalar s) {
  return static_cast<color_component>(s * 255);
}

class color {
public:
  constexpr color(color_component r, color_component g, color_component b,
                  color_component a = 255) noexcept
      : r_{r}, g_{g}, b_{b}, a_{a} {}
  constexpr color_component red() const noexcept { return r_; }
  constexpr color_component green() const noexcept { return g_; }
  constexpr color_component blue() const noexcept { return b_; }
  constexpr color_component alpha() const noexcept { return a_; }

  constexpr static color from_scalars(scalar r, scalar g, scalar b,
                                      scalar a = scalar(1.0)) noexcept {
    return {to_color_component(r), to_color_component(g), to_color_component(b),
            to_color_component(a)};
  }

private:
  color_component r_;
  color_component g_;
  color_component b_;
  color_component a_;
};

namespace colors {
constexpr color red (255, 0, 0);
constexpr color green (0, 255, 0);
constexpr color white (255, 255, 255);
constexpr color black (0, 0, 0);
} // namespace colors
} // namespace graphics
} // namespace kmint

#endif
