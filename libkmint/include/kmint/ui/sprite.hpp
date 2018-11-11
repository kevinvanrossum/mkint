#ifndef KMINT_UI_SPRITE_HPP
#define KMINT_UI_SPRITE_HPP

namespace kmint::ui {

class sprite {
public:
  sprite(texture const &t, isize cutout);

private:
  texture const *texture_;
  isize cutout_;
  vector2d center_{};
  graphics::color tint{graphics::colors::white};
  scalar scale{scalar(1.0)};
};

} // namespace kmint::ui

#endif /* KMINT_UI_SPRITE_HPP */
