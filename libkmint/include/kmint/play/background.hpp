#ifndef KMINT_PLAY_BACKGROUND_HPP
#define KMINT_PLAY_BACKGROUND_HPP

#include "kmint/graphics/image.hpp"
#include "kmint/math/size.hpp"
#include "kmint/play/image_drawable.hpp"
#include "kmint/play/static_actor.hpp"
#include <utility>

namespace kmint::play {

class background : public static_actor {
public:
  background(math::size field_size, graphics::image const &img)
      : static_actor{{field_size.width() * scalar(0.5),
                      field_size.height() * scalar(0.5)}},
        drawable_{*this, img} {}
  ui::drawable const &drawable() const override { return drawable_; }

private:
  image_drawable drawable_;
};

} // namespace kmint::play

#endif /* KMINT_PLAY_BACKGROUND_HPP */
