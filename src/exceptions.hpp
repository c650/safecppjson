#pragma once

#include <cpprest/json.h>

#include <stdexcept>

namespace safecppjson::exceptions {

  template <typename FromType>
  class FromJsonException : public std::exception {
    std::string msg;

  public:
    FromJsonException(void) : msg("error de-serialising JSON ") {
    }

    FromJsonException(const web::json::value& val) : FromJsonException() {
      msg.append(val.serialize());
    }

    FromJsonException(const web::json::value& val, const std::string& msg)
        : FromJsonException(val) {
      this->msg.append(" note: ");
      this->msg.append(msg);
    }

    const char* what(void) const noexcept override {
      return msg.data();
    }
  };

  template <typename ToType>
  class ToJsonException : public std::exception {
    std::string msg;

  public:
    ToJsonException(void) : msg("error serialising JSON ") {
    }

    const char* what(void) const noexcept override {
      return msg.data();
    }
  };

} // namespace safecppjson::exceptions
