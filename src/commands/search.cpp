#include "search.h"
#include "src/arguments.h"
#include "src/database.h"
#include <cstdint>
#include <iostream>
#include <string>

const char diff = 'a' - 'A';

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

bool fuzzy_match(const std::string &str, const std::string with) {
  size_t idx = 0;

  for (char ch : str) {
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

void Search::run(Database::DB *db, Args::SearchFlags flags) {
  auto entries = Database::get_entries(db);

  uint64_t search_cat;
  for (auto entry : entries) {
    switch (flags.search_on) {
    case Args::NAME:
      if (fuzzy_match(*entry->name, flags.search_term)) {
        std::cout << Database::human_str(entry) << std::endl;
      }
      break;
    case Args::CATEGORY:
      search_cat = std::stoi(flags.search_term);
      if (entry->category == search_cat) {
        std::cout << Database::human_str(entry) << std::endl;
      }
      break;
    case Args::USERNAME:
      if (entry->username
              ->transform([&flags](auto s) {
                return fuzzy_match(s, flags.search_term);
              })
              .value_or(false)) {
        std::cout << Database::human_str(entry) << std::endl;
      }
      break;
    case Args::WEBSITE:
      if (entry->website
              ->transform([&flags](auto s) {
                return fuzzy_match(s, flags.search_term);
              })
              .value_or(false)) {
        std::cout << Database::human_str(entry) << std::endl;
      }
      break;
    }
  }
}
