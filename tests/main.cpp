#define CATCH_CONFIG_MAIN
#include <cpprest/json.h>

#include <catch2/catch.hpp>
#include <fstream>

#include "../src/guard_field.hpp"
#include "../src/to_from_json.hpp"

struct Candle {
  double open, high, low, close;

  Candle(void) = default;

  Candle(web::json::value& j)
      : open(safecppjson::guard_field<decltype(open)>(j, "open")),
        high(safecppjson::guard_field<decltype(high)>(j, "high")),
        low(safecppjson::guard_field<decltype(low)>(j, "low")),
        close(safecppjson::guard_field<decltype(close)>(j, "close")) {
  }

  web::json::value serialise(void) {
    web::json::value ret;
    ret["open"] = safecppjson::ToFromJson<decltype(open)>::to(open);
    ret["high"] = safecppjson::ToFromJson<decltype(high)>::to(high);
    ret["low"] = safecppjson::ToFromJson<decltype(low)>::to(low);
    ret["close"] = safecppjson::ToFromJson<decltype(close)>::to(close);
    return ret;
  }
};

TEST_CASE("Valid candle", "[candle]") {
  std::ifstream data{"./tests/json/valid_candle.json"};
  auto j = web::json::value::parse(data);
  data.close();

  auto candle{safecppjson::ToFromJson<Candle>::from(j)};

  REQUIRE(true);
};

TEST_CASE("Missing field candle", "[candle]") {
  std::ifstream data{"./tests/json/missing_field_candle.json"};
  auto j = web::json::value::parse(data);
  data.close();

  try {
    auto candle{safecppjson::ToFromJson<Candle>::from(j)};
  } catch (std::exception& e) {
    std::cerr << e.what() << '\n';
    REQUIRE(true);
  }
};

TEST_CASE("Wrong type in field candle", "[candle]") {
  std::ifstream data{"./tests/json/wrong_type_candle.json"};
  auto j = web::json::value::parse(data);
  data.close();

  try {
    auto candle{safecppjson::ToFromJson<Candle>::from(j)};
  } catch (std::exception& e) {
    std::cerr << e.what() << '\n';
    REQUIRE(true);
  }
};

// ----

struct MoreStuff {
  std::string a;
  double b;
  int c;
  std::optional<Candle> d;
  std::vector<int> e;

  MoreStuff(web::json::value& j)
      : a(safecppjson::guard_field<decltype(a)>(j, "a")),
        b(safecppjson::guard_field<decltype(b)>(j, "b")),
        c(safecppjson::guard_field<decltype(c)>(j, "c")),
        d(safecppjson::guard_field<decltype(d)>(j, "d")),
        e(safecppjson::guard_field<decltype(e)>(j, "e")) {
  }
};

TEST_CASE("Valid MoreStuff", "[morestuff]") {
  std::ifstream data{"./tests/json/valid_more_stuff.json"};
  auto j = web::json::value::parse(data);
  data.close();

  auto candle{safecppjson::ToFromJson<MoreStuff>::from(j)};

  REQUIRE(true);
};
