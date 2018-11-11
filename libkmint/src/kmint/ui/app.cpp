#include "kmint/ui/app.hpp"
#include "SDL.h"
#include "SDL_image.h"
#include "kmint/ui/exceptions.hpp"

namespace kmint::ui {

namespace {
class sdl_base {
public:
  sdl_base() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
      throw initialization_error{std::string{"Error while initializing SDL: "} +
                                 SDL_GetError()};
    }
  }
  sdl_base(sdl_base const &) = delete;
  sdl_base &operator=(sdl_base const &) = delete;
  sdl_base(sdl_base &&) = delete;
  sdl_base &operator=(sdl_base &&) = delete;
  ~sdl_base() { SDL_Quit(); }
};

class sdl_image {
public:
  sdl_image() {
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) !=
        (IMG_INIT_PNG | IMG_INIT_JPG)) {
      throw initialization_error{
          std::string{"Error while initializing SDL_image: "} + IMG_GetError()};
    }
  }
  sdl_image(sdl_image const &) = delete;
  sdl_image &operator=(sdl_image const &) = delete;
  sdl_image(sdl_image &&) = delete;
  sdl_image &operator=(sdl_image &&) = delete;
  ~sdl_image() { IMG_Quit(); }
};
} // namespace

class kmint::ui::app::impl {
private:
  sdl_base base_{};
  sdl_image image_{};
};

app::app() : pimpl_{new impl{}} {}
app::~app() = default;
app::app(app &&) noexcept = default;
app &app::operator=(app &&) noexcept = default;

} // namespace kmint::ui
