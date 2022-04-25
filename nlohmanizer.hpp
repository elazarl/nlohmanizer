#pragma once

#include <nlohmann/json.hpp>

namespace nlohmanizer {
using j = nlohmann::json;

template <size_t N> struct str {
  constexpr str(const char (&str)[N]) { std::copy_n(str, N, s); }
  char s[N];
};

template <typename T, auto... Args> class jsonizer {
  template <typename... TheArgs>
  static void to_json_(j &j, const T &t) {}
  template <str name, auto Ptr, auto... TheArgs>
  static void to_json_(j &j, const T &t) {
    j[name.s] = t.*Ptr;
    to_json_<TheArgs...>(j, t);
  }

  template <typename... TheArgs>
  static void from_json_(const j &j, T &t) {}
  template <str name, auto Ptr, auto... TheArgs>
  static void from_json_(const j &j, T &t) {
    t.*Ptr = j.at(name.s);
    from_json_<TheArgs...>(j, t);
  }

public:
  static void to_json(j &j, const T& t) { to_json_<Args...>(j, t); }
  static void from_json(const j &j, T &t) { from_json_<Args...>(j, t); }
};

} // namespace nlohmanizer
