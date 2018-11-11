#ifndef KMINT_UI_SDL_PTR_HPP
#define KMINT_UI_SDL_PTR_HPP

#include "kmint/ui/sdl/destroy.hpp"
#include <memory>

namespace kmint::ui::sdl {

template <typename T> using unique_ptr = std::unique_ptr<T, destroyer<T>>;

} // namespace kmint::ui::sdl

#endif /* KMINT_UI_SDL_PTR_HPP */
