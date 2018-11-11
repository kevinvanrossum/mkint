#ifndef KMINT_UI_SDL_TEXTURE_HPP
#define KMINT_UI_SDL_TEXTURE_HPP

#include "kmint/graphics/color.hpp"
#include "kmint/math/vector2d.hpp"
#include "kmint/primitives.hpp"
#include "kmint/ui/sdl/ptr.hpp"
#include "kmint/ui/sdl/surface.hpp"

struct SDL_Renderer;

namespace kmint::ui::sdl {

class texture {
public:
  texture(surface const &s, SDL_Renderer *ren)
      : texture_{create(SDL_CreateTextureFromSurface, ren, s)},
        width_{s.width()}, height_{s.height()} {}
  scalar width() const noexcept { return width_; }
  scalar height() const noexcept { return height_; }
  operator SDL_Texture *() const noexcept { return unwrap(); }
  SDL_Texture *unwrap() const noexcept { return texture_.get(); }

private:
  unique_ptr<SDL_Texture> texture_;
  scalar width_;
  scalar height_;
};

void render(SDL_Renderer *ren, sdl::texture const &t, math::vector2d center,
            scalar scale);
void render(SDL_Renderer *ren, sdl::texture const &t, math::vector2d center,
            scalar scale, graphics::color tint);

} // namespace kmint::ui::sdl

#endif /* KMINT_UI_SDL_TEXTURE_HPP */
