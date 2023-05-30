#include "edit.h"
#include "src/arguments.h"
#include "src/database.h"
#include <iostream>
#include <limits>
#include <string>

void Edit::run(Database::DB *db, Args::EditFlags flags) {
  auto opt_entry = Database::get_entry_by_name(db, flags.entry_name);
  if (!opt_entry.has_value()) {
    return;
  }

  auto entry = *opt_entry.value();
  std::string str;

  std::cout << "Name: (" << *entry.name << ") ";
  std::getline(std::cin, str);
  if (!str.empty()) {
    entry.name = new std::string(str);
  }

  std::cout << "Password: (" << *entry.password << ") ";
  std::getline(std::cin, str);
  if (!str.empty()) {
    entry.password = new std::string(str);
  }

  int tmp_int;
  std::cout << "Category: (" << entry.category << ") ";
  std::cin >> tmp_int;
  while (std::cin.fail() || tmp_int < 0) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Error. Please enter a non-negative integer: ";
    std::cin >> tmp_int;
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  entry.category = tmp_int;

  std::cout << "Username: (" << entry.username->value_or("None") << ") ";
  std::getline(std::cin, str);
  if (!str.empty()) {
    entry.username = new std::optional<const std::string>(str);
  }

  std::cout << "Website: (" << entry.website->value_or("None") << ") ";
  std::getline(std::cin, str);
  if (!str.empty()) {
    entry.website = new std::optional<const std::string>(str);
  }

  Database::update_password(db, flags.entry_name, &entry);
}
