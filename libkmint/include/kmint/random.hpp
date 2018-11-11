#ifndef KMINT_RANDOM_HPP
#define KMINT_RANDOM_HPP

#include "kmint/primitives.hpp"

namespace kmint {
//! Generate a random integer in the half open range [low, high)
//! \requires high > low
//! \returns a random integer that is larger than or equal to low and less than
//! high
int random_int(int low, int high);
scalar random_scalar(scalar low, scalar high);
} // namespace kmint
#endif
