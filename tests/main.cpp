#include <cpprest/json.h>

#include <iostream>

#include "../src/include/with_label.hpp"

struct Candle {
  template <typename T>
  using wl = safecppjson::WithLabel<T>;

  wl<std::optional<double>> open, high, low, close;

  Candle(void) = default;

  Candle(web::json::value& j)
      : open("open", j), high("high", j), low("low", j), close("close", j) {
  }

  web::json::value serialise(void) {
    web::json::value ret;
    ret[open.label] = open.to_json();
    ret[high.label] = high.to_json();
    ret[low.label] = low.to_json();
    ret[close.label] = close.to_json();
    return ret;
  }
};

int main(void) {
  web::json::value j;
  j["field"] = 1;

  safecppjson::WithLabel<int32_t> field{"field", j};

  j["stuff"] = web::json::value::parse("[1,2,3]");

  safecppjson::WithLabel<std::vector<int32_t>> stuff{"stuff", j};

  for (auto& e : stuff()) {
    std::cerr << e << "\n";
  }

  safecppjson::WithLabel<std::chrono::milliseconds> field_as_duration{"field",
                                                                      j};

  j = web::json::value::parse("{\"open\":1.0}");
  Candle ca{j};

  safecppjson::WithLabel<std::optional<int32_t>> close{"close", j};

  std::cout << close().has_value() << "\n";

  return 0;
}
