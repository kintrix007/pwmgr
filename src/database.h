#ifndef DATABASE_H
#define DATABASE_H

#include <cstdint>
#include <functional>
#include <istream>
#include <optional>
#include <ostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace Database {
/**
 * The name has to be globally unique.
 */
struct Entry {
  std::string *name;
  std::string *password;
  uint64_t category;
  std::optional<const std::string> *username;
  std::optional<const std::string> *website;

  ~Entry();
};

std::string human_str(const Entry *entry);

typedef std::unordered_map<std::string, Entry *> DB;

Entry *new_entry(const std::string &name, const std::string &password,
                 const uint64_t category,
                 std::optional<const std::string> username,
                 std::optional<const std::string> website);

const std::vector<const Entry *> get_entries(const DB *db);

bool entry_exists(const DB *db, const std::string &entry_name);

std::optional<const Entry *> get_entry_by_name(const DB *db,
                                               const std::string &entry_name);

bool add_password(DB *db, Entry *entry);

bool edit_entry(DB *db, const std::string &entry_name,
                std::function<void(Entry *)> modify);

bool delete_password(DB *db, const std::string &entry_name);
} // namespace Database

std::ostream &operator<<(std::ostream &out, const Database::DB *db);

std::istream &operator>>(std::istream &in, Database::DB *db);

std::ostream &operator<<(std::ostream &out, const Database::Entry *entry);

std::istream &operator>>(std::istream &in, Database::Entry *entry);

#endif
