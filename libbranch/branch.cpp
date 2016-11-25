#include <unordered_map>
#include <mutex>
#include <cstdlib>
#include "json.hpp"

std::once_flag flag;
std::unordered_map<uintptr_t, uintptr_t> taken;
using json = nlohmann::json;

void dump_json()
{
  json j;
  std::transform(std::begin(taken), std::end(taken),
               std::back_inserter(j["branches"]),
    [] (const std::pair<uintptr_t, uintptr_t> &i) -> json {
        return {
            { "address", i.first  },
            { "targets", i.second }
        };
    });
  std::cout << std::setw(2) << j << std::endl;
}

extern "C"
void __note_taken(uintptr_t from, uintptr_t targ) {
  std::call_once(flag, std::atexit, dump_json);
  taken[from] = targ;
}
