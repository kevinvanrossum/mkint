#ifndef KMINT_UI_TEXTURE_HPP
#define KMINT_UI_TEXTURE_HPP

#include <string>
#include <utility>

namespace kmint::ui {

class texture {
public:
  explicit texture(std::string const &fname) : filename_{fname} {}
  explicit texture(std::string &&fname) : filename_{std::move(fname)} {}
  std::string const &filename() const noexcept { return filename_; }

private:
  std::string filename_;
};

} // namespace kmint::ui

#endif /* KMINT_UI_TEXTURE_HPP */
