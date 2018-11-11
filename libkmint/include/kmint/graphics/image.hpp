#ifndef KMINT_GRAPHICS_IMAGE_HPP
#define KMINT_GRAPHICS_IMAGE_HPP

#include "kmint/primitives.hpp"
#include <string>
#include <utility>

namespace kmint {
namespace graphics {

class image {
public:
  explicit image(std::string image_filename, scalar scale = scalar(1.0))
      : filename_{std::move(image_filename)}, scale_{scale} {}
  std::string const &filename() const noexcept { return filename_; }
  scalar scale() const noexcept { return scale_; }
  void scale(scalar new_scale) noexcept { scale_ = new_scale; }

private:
  std::string filename_;
  scalar scale_;
};

} // namespace graphics
} // namespace kmint

#endif
