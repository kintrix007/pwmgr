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
  std::string charset = "";

  if (opts.lower) {
    charset += characters_between('a', 'z');
  }
  if (opts.upper) {
    charset += characters_between('A', 'Z');
  }
  if (opts.numbers) {
    charset += characters_between('0', '9');
  }
  if (opts.symbols) {
    charset += symbols;
  }

  std::stringstream password;
  for (int i = 0; i < opts.length; i++) {
    int idx = rand() % charset.size();
    password << charset[idx];
  }

  return password.str();
}
