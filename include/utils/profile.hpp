#pragma once

#include <chrono>
#include <string>

namespace Profile {
class Timer {
public:
  Timer(const std::string &name);
  ~Timer();

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> _start;
  std::string _name;
};
}; // namespace Profile
