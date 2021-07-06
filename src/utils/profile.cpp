#include "utils/log.hpp"
#include "utils/profile.hpp"
#include <chrono>
#include <string>

Profile::Timer::Timer(const std::string &name) : _name(name) {
  _start = std::chrono::high_resolution_clock::now();
}

Profile::Timer::~Timer() {
  auto end = std::chrono::high_resolution_clock::now();
  auto diff = end - _start;
  Log::message("Profile",
               _name + " -> " + std::to_string(diff.count() * 1e-9) + " sec");
}
