#include "utils/log.hpp"

#include <cstdlib>
#include <iostream>

void Log::message(const std::string module, const std::string msg) {
  std::cout << BOLD << "[" << module << "]: " << RESET;
  std::cout << msg << std::endl;
}

void Log::warn(const std::string module, const std::string msg) {
  std::cout << BOLD << FGYELLOW << "(warning)"
            << "[" << module << "]: " << RESET;
  std::cout << FGYELLOW << msg << RESET << std::endl;
}

void Log::error(const std::string module, const std::string msg,
                bool terminate) {
  std::cout << BOLD << FGRED << "(error)"
            << "[" << module << "]: " << RESET;
  std::cout << FGRED << msg << RESET << std::endl;
  if (terminate)
    exit(EXIT_FAILURE);
}
