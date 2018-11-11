#ifndef KMINT_MAIN_HPP
#define KMINT_MAIN_HPP

#include "kmint/play/actor.hpp"
#include "kmint/play/stage.hpp"
#include "kmint/primitives.hpp"
#include "kmint/ui/drawable.hpp"
#include "kmint/ui/window.hpp"

/*! \defgroup Main The main loop
@{
*/
namespace kmint {

/*! \brief Controls various aspects of the simulation loop

A reference to a \a loop_settings object is given to the callable object \a
given to \ref kmint::main_loop. The behaviour of the simulation can be
controlled by changing the member variables.
*/
struct loop_controls {
  /*! \brief If set to true, the simulation will end.

    In the event that quit is set to true by the main function, the simulation
    will terminate immediately.
   */
  bool quit{false};
  /*! \brief If true, the stage will not be updated.

    This effectively pauses the simulation. The current state will be
    maintained.
   */
  bool pause{false};
  /*! \brief If false, the stage will not be rendered
   */
  bool render{true};
};

/*! \brief The mainloop of a kmint application

  \a main_loop does the following:
  -# It determines the time that passed since the last tick
  -# It calls function \a f with the \ref kmint::delta_time "time delta" and a
  reference to a \ref kmint::loop_controls object
  -# If \a f sets \ref kmint::loop_controls::quit to true, the simulation is
  terminated immediately
  -# Otherwise
    -# If \ref kmint::loop_controls::pause is \a false, \ref kmint::play::stage
  "stage" \a s will have its \ref kmint::play::stage::act "act" method called.
    -# And then, if \ref kmint::loop_controls::render is true, all actors are
  rendered
  -# Go back to step 1

  \param s the \ref kmint::play::stage "stage" which contains the actors
  \param w the \ref kmint::ui::window "window" in which to render the stage
  \param f a callable object that accepts a \ref kmint::delta_time "delta_time"
  \ref kmint::loop_controls object. \ingroup Main
*/
template <typename MainFun>
void main_loop(play::stage &s, ui::window &w, MainFun f) {
  auto wrap = [](auto it) {
    return util::wrap_iterator<ui::drawable const>(
        it, [](play::actor const &a) -> ui::drawable const & {
          return a.drawable();
        });
  };
  time t_prev = now();
  loop_controls ctl{};
  while (true) {
    time t_current = now();
    delta_time dt = t_current - t_prev;
    t_prev = t_current;
    f(dt, ctl);
    if (ctl.quit)
      break;
    if (!ctl.pause)
      s.act(dt);
    if (ctl.render)
      ui::render(w, wrap(s.cbegin()), wrap(s.cend()));
  }
}
} // namespace kmint
/*! @} */

#endif /* KMINT_MAIN_HPP */
