#include "add.h"
#include "src/arguments.h"
#include "src/database.h"
#include "src/generator.h"
#include <iostream>
#include <limits>
#include <optional>
#include <string>

void Add::run(Database::DB *db, Args::AddFlags flags) {
  auto entry = new Database::Entry{};
  entry->name = new std::string{};
  entry->password = Password::generate(flags.password);

  std::string str;

  do {
    std::cout << "Name: ";
    std::getline(std::cin, *entry->name);
  } while (entry->name->empty() || Database::entry_exists(db, *entry->name));

  std::cout << "Password: (" << *entry->password << ") ";
  std::getline(std::cin, str);
  if (!str.empty()) {
    *entry->password = str; // This is a copy
  }

  int tmp_int;
  std::cout << "Category: ";
  std::cin >> tmp_int;
  while (std::cin.fail() || tmp_int < 0) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Error. Please enter a non-negative integer: ";
    std::cin >> tmp_int;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  entry->category = tmp_int;

  if (!flags.only_required) {
    std::cout << "Username: (None) ";
    std::getline(std::cin, str);
    if (str.empty()) {
      entry->username = new std::optional<const std::string>{};
    } else {
      entry->username = new std::optional<const std::string>(str);
    }

    std::cout << "Website: (None) ";
    std::getline(std::cin, str);
    if (str.empty()) {
      entry->website = new std::optional<const std::string>{};
    } else {
      entry->website = new std::optional<const std::string>(str);
    }
  } else {
    entry->username = new std::optional<const std::string>{};
    entry->website = new std::optional<const std::string>{};
  }

  bool ok = Database::add_password(db, entry);

  if (!ok) {
    std::cout << "Sorry, there is already a record with name '" << *entry->name
              << "'. You can try giving it a different name or editing a "
                 "record instead."
              << std::endl;
  }
}
