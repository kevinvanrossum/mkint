#ifndef KMINT_UI_RENDERER_HPP
#define KMINT_UI_RENDERER_HPP

#include "kmint/graphics/color.hpp"
#include "kmint/graphics/image.hpp"
#include "kmint/math/size.hpp"
#include "kmint/math/vector2d.hpp"
#include "kmint/ui/sdl/ptr.hpp"
#include "kmint/ui/sdl/texture.hpp"
#include <map>
#include <memory>

struct SDL_Renderer;
struct SDL_Window;
struct SDL_Texture;

namespace kmint::ui {

class renderer {
public:
  renderer(SDL_Window *w, scalar scale)
      : ren_{sdl::create(SDL_CreateRenderer, w, -1, SDL_RENDERER_ACCELERATED)} {
    SDL_RenderSetScale(ren_.get(), scale, scale);
  }

  void render_color(graphics::color const &color) noexcept;
  graphics::color render_color() const noexcept;
  void render_image(math::vector2d center, graphics::image const &img);
  void render_image(math::vector2d center, graphics::image const &img,
                    graphics::color tint);
  void render_rectangle(math::vector2d center, math::size size);
  void render_line(math::vector2d from, math::vector2d to);
  void begin_frame() noexcept;
  void end_frame() noexcept;

private:
  sdl::texture &get_or_load(graphics::image const &img);
  sdl::unique_ptr<SDL_Renderer> ren_;
  std::map<std::string, sdl::texture> cache_{};
};

} // namespace kmint::ui

#endif /* KMINT_UI_RENDERER_HPP */
