#pragma once

#include <cpprest/json.h>
#include <fmt/core.h>

#include "./exceptions.hpp"
#include "./to_from_json.hpp"

namespace safecppjson {
  using json = web::json::value;

  template <typename T>
  T guard_field(json& j, const std::string& field) {
    try {
      return ToFromJson<T>::from(j[field]);
    } catch (const exceptions::FromJsonException<T>& e) {
      throw exceptions::FromJsonException<T>(
          j, fmt::format("field \"{}\" missing or not correct type", field));
    }
  }
} // namespace safecppjson
