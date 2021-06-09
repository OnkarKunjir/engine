#include "utils/log.hpp"

#include <iostream>

void Log::message(const std::string module, const std::string msg) {
  std::cout << BOLD << "[" << module << "]: " << RESET;
  std::cout << msg << std::endl;
}

void Log::warn(const std::string module, const std::string msg) {
  std::cout << BOLD << FGYELLOW << "[" << module << "]: " << RESET;
  std::cout << FGYELLOW << msg << RESET << std::endl;
}

void Log::error(const std::string module, const std::string msg) {
  std::cout << BOLD << FGRED << "[" << module << "]: " << RESET;
  std::cout << FGRED << msg << RESET << std::endl;
}
