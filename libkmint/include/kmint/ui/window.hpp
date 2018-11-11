#ifndef KMINT_UI_WINDOW_HPP
#define KMINT_UI_WINDOW_HPP

#include "kmint/graphics/color.hpp"
#include "kmint/graphics/image.hpp"
#include "kmint/math/size.hpp"
#include "kmint/math/vector2d.hpp"
#include <memory>
#include <utility>

namespace kmint::ui {

class window;
class texture;

class frame {
public:
  void render_color(graphics::color const &color) noexcept;
  graphics::color render_color() const noexcept;
  void draw_image(math::vector2d center, graphics::image const &img);
  void draw_image(math::vector2d center, graphics::image const &img,
                  graphics::color tint);
  void draw_rectangle(math::vector2d center, math::size size,
                      graphics::color const &color);
  void draw_line(math::vector2d from, math::vector2d to);
  frame(frame const &) = delete;
  frame &operator=(frame const &) = delete;
  frame(frame &&other) noexcept;
  frame &operator=(frame &&other) noexcept;
  ~frame();

  friend class window;

private:
  explicit frame(window &w);
  struct impl;
  std::unique_ptr<impl> pimpl_;
};

class window {
public:
  window(window const & /*other*/) = delete;
  window &operator=(window const & /*other*/) = delete;
  window(window &&other) noexcept;
  window &operator=(window &&other) noexcept;
  ~window();

  class frame frame() {
    return kmint::ui::frame{*this};
  }

  friend class app;
  friend class frame;

private:
  window(math::isize size, char const *title, scalar scale);
  class impl;
  std::unique_ptr<impl> pimpl_;
};

template <typename InputIt> void render(window &w, InputIt begin, InputIt end) {
  frame f{w.frame()};
  for (auto i = begin; i != end; ++i) {
    i->draw(f);
  }
}

} // namespace kmint::ui

#endif
