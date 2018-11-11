#ifndef KMINT_PLAY_IMAGE_DRAWABLE_HPP
#define KMINT_PLAY_IMAGE_DRAWABLE_HPP

#include "kmint/graphics/color.hpp"
#include "kmint/graphics/image.hpp"
#include "kmint/ui/drawable.hpp"
#include <utility>

namespace kmint::ui {
class frame;
} // namespace kmint::ui

namespace kmint::play {

class actor;

class image_drawable : public ui::drawable {
public:
  image_drawable(actor const &owner, graphics::image image)
      : actor_{&owner}, image_{std::move(image)} {}
  image_drawable(actor const &owner, graphics::image image,
                 graphics::color tint)
      : actor_{&owner}, image_{std::move(image)}, tinted_{true}, tint_{tint} {}
  void draw(ui::frame &frame) const override;
  void remove_tint() { tinted_ = false; }
  void set_tint(graphics::color tint) {
    tinted_ = true;
    tint_ = tint;
  }

private:
  actor const *actor_;
  graphics::image image_;
  bool tinted_{false};
  graphics::color tint_{graphics::colors::white};
};

} // namespace kmint::play

#endif /* KMINT_PLAY_IMAGE_DRAWABLE_HPP */
