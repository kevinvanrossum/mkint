#ifndef KMINT_UI_EVENTS_EVENT_HPP
#define KMINT_UI_EVENTS_EVENT_HPP

#include <iterator>

/*! \defgroup Events Classes related to the emision and handling of events
@{
*/
namespace kmint::ui::events {
enum class modifier { none = 0, shift = 0x1, ctrl = 0x2, alt = 0x4 };
enum class key {
  unknown = '\0',
  one = '1',
  two = '2',
  three = '3',
  four = '4',
  five = '5',
  six = '6',
  seven = '7',
  eight = '8',
  nine = '9',
  zero = '0',
  q = 'q',
  w = 'w',
  e = 'e',
  r = 'r',
  t = 't',
  y = 'y',
  u = 'u',
  i = 'i',
  o = 'o',
  p = 'p',
  a = 'a',
  s = 's',
  d = 'd',
  f = 'f',
  g = 'g',
  h = 'h',
  j = 'j',
  k = 'k',
  l = 'l',
  z = 'z',
  x = 'x',
  c = 'c',
  v = 'v',
  b = 'b',
  n = 'n',
  m = 'm',
  opening_bracket = '[',
  closing_bracket = ']',
  space = ' ',
  enter = '\r',
  del,
  backspace,
  left,
  up,
  down,
  right
};
/*! \brief Used by \ref event to signal it does not in fact carry information
 * about an event
 *
 * As such, \a no_event is used by \ref event "event's" default constructor.
 */
struct no_event {};
/*! \brief Signals a user request to terminate the application */
struct quit_event {};
/*! \brief Base class for key events */
struct key_event {
  enum modifier modifier;
  enum key key;
};
/*! \brief Signals a a user released a key */
struct key_up_event : key_event {};
/*! \brief Signals a a user pressed a key */
struct key_down_event : key_event {};

/*! \brief combines two modifiers */
constexpr modifier operator|(modifier lhs, modifier rhs) noexcept {
  using ut = typename std::underlying_type<modifier>::type;
  return static_cast<modifier>(static_cast<ut>(lhs) | static_cast<ut>(rhs));
}
/*! \brief Returns the common modifiers shared by two other modifiers */
constexpr modifier operator&(modifier lhs, modifier rhs) noexcept {
  using ut = typename std::underlying_type<modifier>::type;
  return static_cast<modifier>(static_cast<ut>(lhs) & static_cast<ut>(rhs));
}
constexpr modifier &operator|=(modifier &lhs, modifier rhs) noexcept {
  lhs = lhs | rhs;
  return lhs;
}
/*! \brief Returns true if any modifier key is pressed */
constexpr bool any_modifier(modifier m) noexcept { return m != modifier::none; }
/*! \brief Returns true if a specific modifier is included */
constexpr bool includes_modifier(modifier m, modifier what) noexcept {
  return any_modifier(m & what);
}

/*! \brief A class that carries information about an event

\a event can carry one of a number of events such as the request
to end the application (\ref quit_event), a key press (\ref key_down_event).
and many others.

What type an \a event object carries cannot be determined via a traditional
getter. Instead, the user must call any of the handle methods to specify how an
event must be handled. For instance, the \ref event::handle_quit function
accepts a callable object. \ref event::handle_quit will inspect the internal
state of the event and if it corresponds to a quit event, it will call its
argument with a \ref quit_event object.

Alternatively, the \ref visit method may be called with an object that provides
an overloaded call-operator for each of the different event types.

\a event may be default constructed. In that case, the object holds no event
information. None of the handle functions will respond. An \a event in this
state is said to be invalid. This may be checked by calling \ref event::valid.

*/
class event {
public:
  event() : tag_{tag::none} { e.ne = no_event{}; };
  explicit event(quit_event qe) : tag_{tag::quit} { e.qe = qe; };
  explicit event(key_up_event kue) : tag_{tag::key_up} { e.kue = kue; };
  explicit event(key_down_event kde) : tag_{tag::key_down} { e.kde = kde; };
  template <typename F> void handle_quit(F &&f) const {
    if (tag_ == tag::quit)
      f(e.qe);
  }
  template <typename F> void handle_key_up(F &&f) const {
    if (tag_ == tag::key_up)
      f(e.kue);
  }
  template <typename F> void handle_key_down(F &&f) const {
    if (tag_ == tag::key_down)
      f(e.kde);
  }
  /*! Calls the correct call operator overload on a visitor.

This method should be called with an object that has an overloaded call operator
for each event type. \a visit will inspect the current event and call the
correct overload with the corresponding event object.

## Example

\code{.cpp}
struct event_handler {
  void operator()(quit_event qe) {
    // handle quit event
  }
  void operator()(key_up_event qe) {
    // handle key up event
  }
  void operator()(key_down_event qe) {
    // handle key down event
  }
  // etc.
}

// ...
void process(event e) {
  event_handler handler{};
  e.visit(handler);
}
\endcode

   */
  template <typename Visitor> void visit(Visitor &&f) const {
    switch (tag_) {
    case tag::none:
      break;
    case tag::quit:
      f(e.qe);
      break;
    case tag::key_up:
      f(e.kue);
      break;
    case tag::key_down:
      f(e.kde);
      break;
    }
  }
  /*! \brief Returns whether this object carries actual event information

A default constructed \a event does not contain any event information and is
said to be invalid.

\return true if this object carries event information. False otherwise.
   */
  bool valid() const noexcept { return tag_ != tag::none; }

private:
  enum class tag { none, quit, key_up, key_down } tag_;
  union {
    no_event ne;
    quit_event qe;
    key_up_event kue;
    key_down_event kde;
  } e;
};

class event_source {
public:
  event next() const noexcept;

  class iterator {
  public:
    /*! \brief Constructs the end iterator */
    iterator() {}
    /*! \brief Constructs a normal iterator */
    explicit iterator(event_source const &source)
        : source_{&source}, event_{source.next()} {}
    iterator &operator++() {
      event_ = source_->next();
      return *this;
    }
    iterator operator++(int) {
      auto result = *this;
      this->operator++();
      return result;
    };
    event &operator*() noexcept { return event_; }
    event const &operator*() const noexcept { return event_; }
    bool operator==(iterator const &o) const noexcept {
      return (**this).valid() == (*o).valid();
    }
    bool operator!=(iterator const &o) const noexcept { return !(*this == o); }

  private:
    event_source const *source_{nullptr};
    event event_{};
  };

  iterator begin() const noexcept { return iterator{*this}; }
  iterator end() const noexcept { return iterator{}; }
};

} // namespace kmint::ui::events
/*! @} */

#endif /* KMINT_UI_EVENTS_EVENT_HPP */
