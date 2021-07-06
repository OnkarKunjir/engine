/*
** class to log the events on console.
*/

#pragma once

#include <string>

// color codes
#define RESET "\033[0m"
#define BOLD "\033[1m"

#define FGRED "\033[31m"
#define FGGREEN "\033[32m"
#define FGYELLOW "\033[33m"

class Log {
public:
  static void message(const std::string &module, const std::string &msg);
  static void warn(const std::string &module, const std::string &msg);
  static void error(const std::string &module, const std::string &msg,
                    bool terminate = true);
};
