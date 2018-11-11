#ifndef KMINT_UI_SDL_SURFACE_HPP
#define KMINT_UI_SDL_SURFACE_HPP

#include "SDL.h"
#include "SDL_image.h"
#include "kmint/primitives.hpp"
#include "kmint/ui/sdl/create.hpp"
#include "kmint/ui/sdl/ptr.hpp"
#include <string>

namespace kmint::ui::sdl {

class surface {
public:
  explicit surface(std::string const &filename)
      : surface_{create(IMG_Load, filename.c_str())} {}
  scalar width() const noexcept { return static_cast<scalar>(surface_->w); }
  scalar height() const noexcept { return static_cast<scalar>(surface_->h); }
  operator SDL_Surface *() const noexcept { return surface_.get(); }

private:
  unique_ptr<SDL_Surface> surface_;
};


} // namespace kmint::ui::sdl

#endif /* KMINT_UI_SDL_SURFACE_HPP */
