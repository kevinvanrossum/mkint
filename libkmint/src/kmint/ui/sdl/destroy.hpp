#ifndef KMINT_UI_SDL_DESTROY_HPP
#define KMINT_UI_SDL_DESTROY_HPP

#include "SDL.h"
#include "SDL_image.h"

namespace kmint::ui::sdl {

template <typename T> class destroyer {
public:
  void operator()(T *ptr) const noexcept {
    if (ptr)
      destroy(ptr);
  }

private:
  static void destroy(SDL_Window *w) noexcept { SDL_DestroyWindow(w); }
  static void destroy(SDL_Texture *t) noexcept { SDL_DestroyTexture(t); }
  static void destroy(SDL_Renderer *r) noexcept { SDL_DestroyRenderer(r); }
  static void destroy(SDL_Surface *s) noexcept { SDL_FreeSurface(s); }
};

template <typename T> void destroy(T *ptr) noexcept {
  destroyer<T> d{};
  d(ptr);
}

} // namespace kmint::ui::sdl

#endif /* KMINT_UI_SDL_DESTROY_HPP */
