#ifndef KMINT_PRIMITIVES_HPP
#define KMINT_PRIMITIVES_HPP

#include <chrono>
namespace kmint {
using scalar = float;

using timer = std::chrono::steady_clock;
using time = timer::time_point;
using delta_time = timer::duration;

inline time now() { return timer::now(); }

inline float to_seconds(delta_time dt) {
  return std::chrono::duration_cast<std::chrono::duration<float>>(dt).count();
}

inline delta_time from_seconds(float sec) {
  return std::chrono::duration_cast<delta_time>(
      std::chrono::duration<float>(sec));
}

} // namespace kmint

#endif /* KMINT_PRIMITIVES_HPP */
