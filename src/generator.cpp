#include "generator.h"
#include <cstdlib>
#include <sstream>
#include <string>

static std::string symbols = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

static std::string characters_between(const char first, const char last) {
  int size = last - first + 1;
  std::string chars(size, '\0');

  char ch = first;
  for (int i = 0; i < size; i++) {
    chars[i] = ch;
    ch++;
  }

  return chars;
}

std::string Password::generate(const Options &opts) {
  std::stringstream charset_stream;

  if (opts.lower) {
    charset_stream << characters_between('a', 'z');
  }
  if (opts.upper) {
    charset_stream << characters_between('A', 'Z');
  }
  if (opts.numbers) {
    charset_stream << characters_between('0', '9');
  }
  if (opts.symbols) {
    charset_stream << symbols;
  }

  std::string charset = charset_stream.str();
  std::string password(opts.length, '\0');

  for (int i = 0; i < opts.length; i++) {
    int idx = rand() % charset.size();
    password[i] = charset[idx];
  }

  return password;
}
