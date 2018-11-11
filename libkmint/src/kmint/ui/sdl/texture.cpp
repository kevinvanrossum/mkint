#include "kmint/ui/sdl/texture.hpp"
#include "SDL.h"
#include "kmint/ui/sdl/utility.hpp"

namespace kmint::ui::sdl {

namespace {

class texture_tint {
public:
  texture_tint(sdl::texture const &texture, graphics::color c)
      : texture_{&texture} {
    apply_rgb(SDL_SetTextureColorMod, c, texture_->unwrap());
  }
  ~texture_tint() {
    apply_rgb(SDL_SetTextureColorMod, graphics::colors::white,
              texture_->unwrap());
  }

private:
  sdl::texture const *texture_;
};
} // namespace

void render(SDL_Renderer *ren, sdl::texture const &t, math::vector2d center,
            scalar scale) {
  auto w = t.width() * scale;
  auto h = t.height() * scale;
  auto x = center.x() - w / 2.0;
  auto y = center.y() - h / 2.0;

  SDL_Rect r;
  r.x = static_cast<int>(x);
  r.y = static_cast<int>(y);
  r.w = static_cast<int>(w);
  r.h = static_cast<int>(h);
  SDL_RenderCopyEx(ren, t.unwrap(), nullptr, &r, 0.0, NULL, SDL_FLIP_NONE);
}
void render(SDL_Renderer *ren, sdl::texture const &t, math::vector2d center,
            scalar scale, graphics::color tint) {
  texture_tint tt{t, tint};
  render(ren, t, center, scale);
}
} // namespace kmint::ui::sdl
