#include "search_utils.h"
#include <cstddef>

bool is_equal_ci(char x, char y) {
  bool is_equal = false;
  if ('a' <= x && x <= 'z' && x - diff == y) {
    is_equal = true;
  }
  if ('A' <= x && x <= 'Z' && x + diff == y) {
    is_equal = true;
  }

  return is_equal || x == y;
}

bool fuzzy_match(const std::string &str, const std::string &with) {
  size_t idx = 0;

  for (const char ch : str) {
    if (!is_equal_ci(with[idx], ch)) {
      continue;
    }
    idx++;
    if (idx == with.size()) {
      return true;
    }
  }

  return false;
}

