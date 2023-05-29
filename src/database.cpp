#include "src/database.h"
#include <optional>
#include <string>
#include <vector>

Database::Entry::~Entry() {
  delete this->name;
  delete this->password;
  delete this->username;
  delete this->website;
}

Database::Entry *
Database::new_entry(const std::string &name, const std::string &password,
                    const uint64_t category,
                    std::optional<const std::string> username,
                    std::optional<const std::string> website) {
  return new Entry{
    .name = new std::string(name),
    .password = new std::string(password),
    .category = category,
    .username = new std::optional(username),
    .website  = new std::optional(website),
  };
}

const std::vector<Database::Entry *> Database::get_entries(const DB *db) {
  std::vector<Database::Entry *> entries;

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

void Database::update_password(DB *db, const std::string &entry_name,
                               const Entry *new_entry) {
  auto entry = db->at(entry_name);

  if (entry->name != new_entry->name) {
    entry->name = new_entry->name;
    db->erase(entry_name);
    db->insert({*entry->name, entry});
  }

  if (entry->password != new_entry->password) {
    entry->password = new_entry->password;
  }

  if (entry->category != new_entry->category) {
    entry->category = new_entry->category;
  }

  if (entry->username != new_entry->username) {
    entry->username = new_entry->username;
  }

  if (entry->website != new_entry->website) {
    entry->website = new_entry->website;
  }
}

bool Database::delete_password(DB *db, const std::string &entry_name) {
  if (!entry_exists(db, entry_name)) {
    return false;
  }

  delete db->at(entry_name);
  db->erase(entry_name);
  return true;
}
