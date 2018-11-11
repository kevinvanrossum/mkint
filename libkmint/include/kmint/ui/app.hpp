#ifndef KMINT_UI_APP_HPP
#define KMINT_UI_APP_HPP

#include "kmint/ui/window.hpp"
#include <memory>
#include <string>

namespace kmint::ui {

/*! \brief Entry point for ui applications.

    \a app initializes the ui layer for use. It will deinitialize the layer
    when it is destructed.

    \a app therefore serves as an entry point for GUI-applications. The only
    way to obtain a window instance is by calling \ref app::create_window.

    At any given moment, at most one app-object should exist.
*/
class app {
public:
  //! \brief Construct an ui app, initializing all UI subsystems.
  //! \throw initialization_error Indicates one of the UI sublayers failed to
  //! initialize
  app();
  ~app();
  app(app const &) = delete;
  app &operator=(app const &) = delete;
  app(app &&) noexcept;
  app &operator=(app &&) noexcept;
  //! \brief Construct a window
  //!
  //! \ref kmint::ui::window "window's" constructor is private to prevent
  //! windows from being created without an initialized ui subsystem. This
  //! method will forward its arguments to window's constructor.
  //!
  //! \param size the dimensions of the window
  //! \param title title of the window
  //! \param scale optional scale factor (defaults to 1.0)
  //! \return a window object.
  window create_window(math::isize size, char const *title,
                       scalar scale = scalar(1.0)) {
    return {size, title, scale};
  }

private:
  class impl;
  std::unique_ptr<impl> pimpl_;
};

} // namespace kmint::ui

#endif /* KMINT_UI_APP_HPP */
