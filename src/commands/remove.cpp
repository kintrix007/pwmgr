#include "remove.h"
#include "src/arguments.h"
#include "src/database.h"
#include <iostream>

void Remove::run(Database::DB *db, Args::RemoveFlags flags) {
  if (flags.entry_names.size() == 0) {
    std::cout << "There is nothing to delete." << std::endl;
    return;
  }

  std::cout << "The following entries will be deleted:" << std::endl;
  for (auto name : flags.entry_names) {
    auto entry = Database::get_entry_by_name(db, name);
    if (!entry.has_value()) {
      continue;
    }
    std::cout << Database::human_str(entry.value()) << std::endl;
  }

  std::cout << "Is this correct? (y/n) ";
  char ch;
  std::cin >> ch;

  if (ch != 'y' && ch != 'Y') {
    std::cout << "Aborted." << std::endl;
    return;
  }

  for (auto name : flags.entry_names) {
    Database::delete_password(db, name);
  }
}
