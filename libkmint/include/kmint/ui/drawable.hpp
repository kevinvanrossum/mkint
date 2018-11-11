#ifndef KMINT_UI_DRAWABLE_HPP
#define KMINT_UI_DRAWABLE_HPP

#include <memory>
#include <utility>

namespace kmint::ui {

class frame;

class drawable {
public:
  drawable() = default;
  drawable(drawable const &) = delete;
  drawable(drawable &&) = delete;
  drawable &operator=(drawable const &) = delete;
  drawable &operator=(drawable &&) = delete;
  virtual ~drawable() = default;

  virtual void draw(frame &f) const = 0;
};

} // namespace kmint::ui

#endif
