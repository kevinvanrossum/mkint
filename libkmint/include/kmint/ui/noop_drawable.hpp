#ifndef KMINT_UI_NOOP_DRAWABLE_HPP
#define KMINT_UI_NOOP_DRAWABLE_HPP

#include "kmint/ui/drawable.hpp"

namespace kmint {
namespace ui {

class frame;

class noop_drawable : public drawable {
  void draw(frame &f) const override {}
};

} // namespace ui

} // namespace kmint

#endif /* KMINT_UI_NOOP_DRAWABLE_HPP */
