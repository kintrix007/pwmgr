#include "src/database.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

Database::Entry::~Entry() {
  delete this->name;
  delete this->password;
  delete this->username;
  delete this->website;
}

std::string Database::human_str(const Database::Entry *entry) {
  std::stringstream ss;

  ss << "[" << *entry->name << "]" << std::endl;
  if (entry->website->has_value()) {
    ss << "Website:  " << entry->website->value() << std::endl;
  }
  if (entry->username->has_value()) {
    ss << "Username: " << entry->username->value() << std::endl;
  }
  ss << "Password: " << *entry->password << std::endl;
  ss << "Category: " << entry->category << std::endl;

  return ss.str();
}

Database::Entry *Database::new_entry(const std::string &name,
                                     const std::string &password,
                                     const uint64_t category,
                                     std::optional<const std::string> username,
                                     std::optional<const std::string> website) {
  return new Entry{
      .name = new std::string(name),
      .password = new std::string(password),
      .category = category,
      .username = new std::optional(username),
      .website = new std::optional(website),
  };
}

const std::vector<const Database::Entry *> Database::get_entries(const DB *db) {
  std::vector<const Database::Entry *> entries;

  for (const auto &[_, entry] : *db) {
    entries.push_back(entry);
  }

  return entries;
}

bool Database::entry_exists(const DB *db, const std::string &entry_name) {
  return db->find(entry_name) != db->end();
}

std::optional<const Database::Entry *>
Database::get_entry_by_name(const DB *db, const std::string &entry_name) {
  if (!entry_exists(db, entry_name)) {
    return {};
  }
  return db->at(entry_name);
}

bool Database::add_password(DB *db, Entry *entry) {
  return db->insert({*entry->name, entry}).second;
}

bool Database::edit_entry(Database::DB *db, const std::string &entry_name,
                std::function<void(Database::Entry *)> mofify) {
  if (!entry_exists(db, entry_name)) {
    return false;
  }

  auto entry = db->at(entry_name);
  mofify(entry);

  if (entry->name->compare(entry_name) != 0) {
    db->erase(entry_name);
    db->insert({*entry->name, entry});
  }

  return true;
}

bool Database::delete_password(DB *db, const std::string &entry_name) {
  if (!entry_exists(db, entry_name)) {
    return false;
  }

  delete db->at(entry_name);
  db->erase(entry_name);
  return true;
}

std::ostream &operator<<(std::ostream &out, const Database::DB *db) {
  auto entries = Database::get_entries(db);

  out << entries.size() << std::endl;
  for (auto e : entries) {
    out << e << std::endl;
  }

  return out;
}

std::istream &operator>>(std::istream &in, Database::DB *db) {
  int size;
  in >> size;
  in.ignore(1, '\n');

  for (int i = 0; i < size; i++) {
    auto entry = new Database::Entry;
    in >> entry;
    in.ignore(1, '\n');
    Database::add_password(db, entry);
  }

  return in;
}

std::ostream &operator<<(std::ostream &out, const Database::Entry *entry) {
  std::string field;

  field = *entry->name;
  out << field.size() << " " << field;
  field = *entry->password;
  out << field.size() << " " << field;
  out << entry->category << " ";
  field = entry->username->value_or("");
  out << field.size() << " " << field;
  field = entry->website->value_or("");
  out << field.size() << " " << field;

  return out;
}

std::istream &take_n_chars(std::istream &in, std::string *str, int n) {
  str->clear();
  char *chars = new char[n + 2];

  in.read(chars, n + 1);
  *str = chars + 1;

  delete[] chars;
  return in;
}

std::istream &operator>>(std::istream &in, Database::Entry *entry) {
  int size;

  entry->name = new std::string;
  in >> size;
  take_n_chars(in, entry->name, size);

  entry->password = new std::string;
  in >> size;
  take_n_chars(in, entry->password, size);

  in >> entry->category;

  in >> size;
  if (size == 0) {
    entry->username = new std::optional<const std::string>({});
  } else {
    std::string str;
    take_n_chars(in, &str, size);
    auto username = new std::optional<const std::string>(str);
    entry->username = username;
  }

  in >> size;
  if (size == 0) {
    entry->website = new std::optional<const std::string>({});
  } else {
    std::string str;
    take_n_chars(in, &str, size);
    auto website = new std::optional<const std::string>(str);
    entry->website = website;
  }

  return in;
}
