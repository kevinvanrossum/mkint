#ifndef KMINT_UI_SDL_CREATE_HPP
#define KMINT_UI_SDL_CREATE_HPP

#include "SDL.h"
#include "kmint/ui/exceptions.hpp"

namespace kmint::ui::sdl {

template <typename F, typename... Args>
decltype(auto) create(F &&creator, Args &&... args) {
  auto r = creator(std::forward<Args>(args)...);
  if (r == nullptr) {
    throw initialization_error{SDL_GetError()};
  }
  return r;
}

} // namespace kmint::ui::sdl

#endif /* KMINT_UI_SDL_CREATE_HPP */
