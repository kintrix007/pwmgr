#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdint>
#include <string>

namespace Password {
struct Options {
  uint16_t length;
  bool upper;
  bool lower;
  bool numbers;
  bool symbols;
};

std::string generate(const Options &opts);
} // namespace Password

#endif
