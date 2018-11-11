#ifndef KMINT_PLAY_TEXTURE_DRAWABLE_HPP
#define KMINT_PLAY_TEXTURE_DRAWABLE_HPP

#include "kmint/ui/drawable.hpp"
#include "kmint/ui/texture.hpp"
#include <utility>

namespace kmint::ui {
class frame;
} // namespace kmint::ui

namespace kmint::play {

class actor;

class texture_drawable : public ui::drawable {
public:
  texture_drawable(actor const &owner, ui::texture texture)
      : actor_{&owner}, texture_{std::move(texture)} {}
  void draw(ui::frame &frame) const override;

private:
  actor const *actor_;
  ui::texture texture_;
};

} // namespace kmint::play

#endif /* KMINT_PLAY_TEXTURE_DRAWABLE_HPP */
