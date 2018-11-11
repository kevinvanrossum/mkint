#include "kmint/play/texture_drawable.hpp"
#include "kmint/math/vector2d.hpp"
#include "kmint/play/actor.hpp"
#include "kmint/ui/window.hpp"
namespace kmint::play {

void texture_drawable::draw(ui::frame &f) const {
  f.draw_texture(actor_->location(), texture_);
}

} // namespace kmint::play
