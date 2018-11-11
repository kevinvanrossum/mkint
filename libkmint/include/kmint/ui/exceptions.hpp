#ifndef KMINT_UI_EXCEPTIONS_HPP
#define KMINT_UI_EXCEPTIONS_HPP

#include <stdexcept>

namespace kmint::ui {

class initialization_error : public std::runtime_error {
public:
  explicit initialization_error(std::string const &what)
      : std::runtime_error{what} {}
  explicit initialization_error(char const *what) : std::runtime_error{what} {}
};

} // namespace kmint::ui

#endif /* KMINT_UI_EXCEPTIONS_HPP */
