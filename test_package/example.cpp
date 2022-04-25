#include <string>
#include <iostream>

#include "nlohmanizer.hpp"

struct s {
  int a;
  std::string name;
};

using s_json = nlohmanizer::jsonizer<s, nlohmanizer::str("a"), &s::a, nlohmanizer::str("name"), &s::name>;
using nlohmann::json;

void to_json(json& j, const s& s) { s_json::to_json(j, s); }
void from_json(const json& j, s& s) { s_json::from_json(j, s); }


int main() {
  using namespace std;
  string json_str = R"(
  {
    "a": 1,
    "name": "koko"
  }
  )";
  s s{-1};
  auto j = json::parse(json_str);
  j.update({{"x", "y"}});
  s = j.get<struct s>();
  assert(s.a == 1);
  assert(s.name == "koko");

  s.name = "xxx";
  s.a = 42;

  j = s;
  assert(j.at("name").get<string>() == "xxx");
  assert(j.at("a").get<int>() == 42);
}
