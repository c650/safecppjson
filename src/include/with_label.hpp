/// \file with_label.hpp
/// \brief

#pragma once

#include <cpprest/json.h>

#include "./to_from_json.hpp"

namespace safecppjson {
  template <typename T>
  class WithLabel {
    using json = web::json::value;
    T member;

  public:
    const std::string label;

    WithLabel(void) = delete;

    WithLabel(const std::string& label) : label(label), member() {
    }

    WithLabel(const std::string& label, const T& member)
        : label(label), member(member) {
    }

    WithLabel(const std::string& label, json& j)
        : label(label), member(ToFromJson<T>::from(j[label])) {
    }

    T& operator()() {
      return member;
    }

    const T& operator()() const {
      return member;
    }

    json to_json(void) const {
      return ToFromJson<T>::to(member);
    }
  };

  template <typename T>
  class WithLabel<std::optional<T>> {
    using json = web::json::value;
    std::optional<T> member;

  public:
    const std::string label;

    WithLabel(void) = delete;

    WithLabel(const std::string& label) : label(label) {
    }

    WithLabel(const std::string& label, const T& member)
        : label(label), member(member) {
    }

    WithLabel(const std::string& label, json& j) : label(label) {
      if (ToFromJson<T>::validate(j["label"])) {
        member.emplace(ToFromJson<T>::from(j["label"]));
      }
    }

    std::optional<T>& operator()() {
      return member;
    }

    const std::optional<T>& operator()() const {
      return member;
    }

    json to_json(void) const {
      if (!member.has_value()) {
        return json::value::null();
      }
      return ToFromJson<T>::to(member.value());
    }
  };
} // namespace safecppjson
