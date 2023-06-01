#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

const char diff = 'a' - 'A';

bool is_equal_ci(char x, char y);

bool fuzzy_match(const std::string &str, const std::string &with);

#endif
