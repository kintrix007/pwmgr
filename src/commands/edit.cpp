#include "edit.h"
#include "src/arguments.h"
#include "src/database.h"
#include <iostream>
#include <limits>
#include <string>

void Edit::run(Database::DB *db, Args::EditFlags flags) {
  bool exists =
      Database::edit_entry(db, flags.entry_name, [](Database::Entry *entry) {
        std::string str;

        std::cout << "Name: (" << *entry->name << ") ";
        std::getline(std::cin, str);
        if (!str.empty()) {
          *entry->name = str;
        }

        std::cout << "Password: (" << *entry->password << ") ";
        std::getline(std::cin, str);
        if (!str.empty()) {
          *entry->password = str;
        }

        int tmp_int;
        std::cout << "Category: (" << entry->category << ") ";
        std::cin >> tmp_int;
        while (std::cin.fail() || tmp_int < 0) {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Error. Please enter a non-negative integer: ";
          std::cin >> tmp_int;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        entry->category = tmp_int;

        std::cout << "Username: (" << entry->username->value_or("None") << ") ";
        std::getline(std::cin, str);
        if (!str.empty()) {
          delete entry->username;
          entry->username = new std::optional<const std::string>(str);
        }

        std::cout << "Website: (" << entry->website->value_or("None") << ") ";
        std::getline(std::cin, str);
        if (!str.empty()) {
          delete entry->website;
          entry->website = new std::optional<const std::string>(str);
        }
      });

  if (!exists) {
    std::cout << "No such entry '" << flags.entry_name << "'." << std::endl;
  }
}
