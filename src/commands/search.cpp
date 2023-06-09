#include "search.h"
#include "src/arguments.h"
#include "src/database.h"
#include "src/search_utils.h"
#include <cstdint>
#include <iostream>
#include <string>

void Search::run(Database::DB *db, const Args::SearchFlags &flags) {
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
