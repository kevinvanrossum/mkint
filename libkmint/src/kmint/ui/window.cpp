#include "kmint/ui/window.hpp"
#include "SDL.h"
#include "kmint/graphics/color.hpp"
#include "kmint/graphics/image.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/play/actor.hpp"
#include "kmint/play/stage.hpp"
#include "kmint/ui/app.hpp"
#include "kmint/ui/drawable.hpp"
#include "kmint/ui/renderer.hpp"
#include "kmint/ui/sdl/create.hpp"
#include "kmint/ui/sdl/ptr.hpp"
#include <stdexcept>
#include <unordered_map>
#include <utility>

namespace kmint::ui {

class window::impl {
public:
  friend class frame;
  impl(math::isize size, char const *title, scalar scale)
      : win_{sdl::create(SDL_CreateWindow, title, SDL_WINDOWPOS_UNDEFINED,
                         SDL_WINDOWPOS_UNDEFINED, size.width() * scale,
                         size.height() * scale, SDL_WINDOW_OPENGL)},
        ren_{win_.get(), scale} {}

  renderer &get_renderer() noexcept { return ren_; }

private:
  sdl::unique_ptr<SDL_Window> win_;
  renderer ren_;
};

/* FRAME */
struct frame::impl {
  renderer *ren_;
};

frame::frame(window &w) : pimpl_{new frame::impl{&w.pimpl_->get_renderer()}} {
  pimpl_->ren_->begin_frame();
}
frame::frame(frame &&other) noexcept = default;
frame &frame::operator=(frame &&other) noexcept = default;
frame::~frame() { pimpl_->ren_->end_frame(); }
void frame::render_color(graphics::color const &color) noexcept {
  pimpl_->ren_->render_color(color);
}
graphics::color frame::render_color() const noexcept {
  return pimpl_->ren_->render_color();
}

void frame::draw_image(math::vector2d center, graphics::image const &img) {
  pimpl_->ren_->render_image(center, img);
}
void frame::draw_image(math::vector2d center, graphics::image const &img,
                       graphics::color tint) {
  pimpl_->ren_->render_image(center, img, tint);
}
void frame::draw_rectangle(math::vector2d center, math::size size,
                           graphics::color const &color) {
  pimpl_->ren_->render_color(color);
  pimpl_->ren_->render_rectangle(center, size);
}

void frame::draw_line(math::vector2d from, math::vector2d to) {
  pimpl_->ren_->render_line(from, to);
}

/* WINDOW */
window::window(math::isize size, char const *title, scalar scale)
    : pimpl_{new window::impl{size, title, scale}} {}

window::~window() = default;
window::window(window && /*other*/) noexcept = default;
window &window::operator=(window && /*other*/) noexcept = default;

} // namespace kmint::ui
