#include "kmint/ui/events/event.hpp"
#include "SDL.h"

namespace kmint::ui::events {
namespace {
template <typename T, typename... Args>
constexpr bool contains(T val, Args &&... args) noexcept {
  return ((val & args) || ... || false);
}
modifier to_modifier(SDL_Keysym ks) noexcept {
  modifier result{};
  if (contains(ks.mod, KMOD_LCTRL, KMOD_RCTRL)) {
    result |= modifier::ctrl;
  }
  if (contains(ks.mod, KMOD_LALT, KMOD_RALT)) {
    result |= modifier::alt;
  }
  if (contains(ks.mod, KMOD_LSHIFT, KMOD_RSHIFT)) {
    result |= modifier::shift;
  }
  return result;
}
key to_key(SDL_Keysym ks) noexcept {
  if (ks.scancode >= SDL_SCANCODE_A && ks.scancode <= SDL_SCANCODE_Z) {
    return static_cast<key>('a' + ks.scancode - SDL_SCANCODE_A);
  } else if (ks.scancode >= SDL_SCANCODE_1 && ks.scancode <= SDL_SCANCODE_9) {
    return static_cast<key>('1' + ks.scancode - SDL_SCANCODE_1);
  } else if (ks.scancode == SDL_SCANCODE_0) {
    return key::zero;
  }
  switch (ks.scancode) {
  case SDL_SCANCODE_RETURN:
    return key::enter;
  case SDL_SCANCODE_DELETE:
    return key::del;
  case SDL_SCANCODE_BACKSPACE:
    return key::backspace;
  case SDL_SCANCODE_LEFT:
    return key::left;
  case SDL_SCANCODE_RIGHT:
    return key::right;
  case SDL_SCANCODE_UP:
    return key::up;
  case SDL_SCANCODE_DOWN:
    return key::down;
  case SDL_SCANCODE_LEFTBRACKET:
    return key::opening_bracket;
  case SDL_SCANCODE_RIGHTBRACKET:
    return key::closing_bracket;
  default:
    return key::unknown;
  }
}

template <typename T> event build_key_event(SDL_Event &e) noexcept {
  T result{};
  result.modifier = to_modifier(e.key.keysym);
  result.key = to_key(e.key.keysym);
  return event{result};
}

} // namespace
event event_source::next() const noexcept {
  SDL_Event e;
  // return any event that we can handle
  while (SDL_PollEvent(&e) != 0) {
    switch (e.type) {
    case SDL_QUIT:
      return event{quit_event{}};
    case SDL_KEYDOWN:
      return build_key_event<key_down_event>(e);
    case SDL_KEYUP:
      return build_key_event<key_up_event>(e);
    default:
      break;
    }
  }
  // we exhausted all events, and couldn't find one we are
  // supposed to return to our caller
  return {};
}
} // namespace kmint::ui::events
