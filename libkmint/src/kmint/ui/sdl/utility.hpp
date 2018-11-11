#ifndef KMINT_UI_SDL_UTILITY_HPP
#define KMINT_UI_SDL_UTILITY_HPP

#include "kmint/graphics/color.hpp"

namespace kmint::ui::sdl {

template <typename F, typename... Args>
decltype(auto) apply_rgb(F &&f, graphics::color c, Args &&... args) {
  return f(std::forward<Args>(args)..., c.red(), c.green(), c.blue());
}
template <typename F, typename... Args>
decltype(auto) apply_rgba(F &&f, graphics::color c, Args &&... args) {
  return f(std::forward<Args>(args)..., c.red(), c.green(), c.blue(),
           c.alpha());
}

} // namespace kmint::ui::sdl

#endif /* KMINT_UI_SDL_UTILITY_HPP */
