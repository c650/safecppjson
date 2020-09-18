#pragma once

#include <cpprest/json.h>

#include "./exceptions.hpp"

namespace safecppjson {
  using json = web::json::value;

  template <typename T>
  struct ToFromJson {
    static bool validate(json&) {
      return true;
    }
    static T from(json& j) {
      return T{j};
    }
    static json to(const T& o) {
      return o.serialise();
    }
  };

  template <>
  struct ToFromJson<int32_t> {
    static bool validate(json& j) {
      return j.is_number() && j.as_number().is_int32();
    }

    static int32_t from(json& j) {
      if (!validate(j)) {
        throw exceptions::FromJsonException<int32_t>{j};
      }
      return j.as_number().to_int32();
    }

    static json to(const int32_t& v) {
      return json{v};
    }
  };

  template <>
  struct ToFromJson<int64_t> {
    static bool validate(json& j) {
      return j.is_number() && j.as_number().is_int64();
    }

    static int64_t from(json& j) {
      if (!validate(j)) {
        throw exceptions::FromJsonException<int64_t>{j};
      }
      return j.as_number().to_int64();
    }

    static json to(const int64_t& v) {
      return json{v};
    }
  };

  template <>
  struct ToFromJson<uint32_t> {
    static bool validate(json& j) {
      return j.is_number() && j.as_number().is_uint32();
    }

    static uint32_t from(json& j) {
      if (!validate(j)) {
        throw exceptions::FromJsonException<uint32_t>{j};
      }
      return j.as_number().to_uint32();
    }

    static json to(const uint32_t& v) {
      return json{v};
    }
  };

  template <>
  struct ToFromJson<uint64_t> {
    static bool validate(json& j) {
      return j.is_number() && j.as_number().is_uint64();
    }

    static uint64_t from(json& j) {
      if (!validate(j)) {
        throw exceptions::FromJsonException<uint64_t>{j};
      }
      return j.as_number().to_uint64();
    }

    static json to(const uint64_t& v) {
      return json{v};
    }
  };

  template <>
  struct ToFromJson<double> {
    static bool validate(json& j) {
      return j.is_double();
    }

    static double from(json& j) {
      if (!validate(j)) {
        throw exceptions::FromJsonException<double>{j};
      }
      return j.as_double();
    }

    static json to(const double& v) {
      return json{v};
    }
  };

  template <>
  struct ToFromJson<std::string> {
    static bool validate(json& j) {
      return j.is_string();
    }

    static std::string from(json& j) {
      if (!validate(j)) {
        throw exceptions::FromJsonException<std::string>{j};
      }
      return j.as_string();
    }

    static json to(const std::string& v) {
      return json{v};
    }
  };

  template <typename T>
  struct ToFromJson<std::vector<T>> {
    static bool validate(json& j) {
      return j.is_array();
    }

    static std::vector<T> from(json& j) {
      if (!validate(j)) {
        throw exceptions::FromJsonException<std::vector<T>>{j};
      }
      std::vector<T> ret{};
      auto& js = j.as_array();
      std::transform(js.begin(), js.end(), std::back_inserter(ret),
                     ToFromJson<T>::from);
      return ret;
    }

    static json to(const std::vector<T>& v) {
      json ret;
      std::transform(v.cbegin(), v.cend(), std::back_inserter(ret),
                     ToFromJson<T>::to);
      return ret;
    }
  };

  // template <typename K, typename V>
  // struct ToFromJson<std::unordered_map<K, V>> {
  //   static bool validate(json& j) {
  //   }

  //   static std::unordered_map<K, V> from(json& j) {
  //     if (!validate(j)) {
  //       throw exceptions::FromJsonException<std::unordered_map<K, V>>{j};
  //     }
  //     return {};
  //   }

  //   static json to(const std::unordered_map<K, V>& v) {
  //     return {};
  //   }
  // };

  template <>
  struct ToFromJson<json> {
    static bool validate(json& j) {
      return true;
    }

    static json from(json& j) {
      return j;
    }

    static json to(const json& v) {
      return v;
    }
  };

  template <typename _Rep, typename _Ratio>
  struct ToFromJson<std::chrono::duration<_Rep, _Ratio>> {
    using DType = std::chrono::duration<_Rep, _Ratio>;
    static bool validate(json& j) {
      return j.is_number() && j.as_number().is_uint64();
    }

    static DType from(json& j) {
      if (!validate(j)) {
        throw exceptions::FromJsonException<DType>{j};
      }
      return DType{j.as_number().to_uint64()};
    }

    static json to(const DType& v) {
      return json{v.count()};
    }
  };
  // fdfd
} // namespace safecppjson
