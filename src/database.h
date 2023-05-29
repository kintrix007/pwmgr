#ifndef DATABASE_H
#define DATABASE_H

#include <cstdint>
#include <optional>
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

  ~Entry() {
    delete this->name;
    delete this->password;
    delete this->username;
    delete this->website;
  }
};

typedef std::unordered_map<std::string, Entry *> DB;

const std::vector<Entry *> get_entries(const DB *db);

inline bool entry_exists(const DB *db, const std::string &entry_name);

std::optional<const Entry *> get_entry_by_name(const DB *db,
                                               const std::string &entry_name);

inline bool add_password(DB *db, Entry *entry);

/*
 * Instead of replacing the previous entry with the new one,
 * copy the given contents of the given enrty into the pre-existing one
 * due to completely arbitrary functional requrements...
 */
void update_password(DB *db, const std::string &entry_name,
                     const Entry *new_entry);

bool delete_password(DB *db, const std::string &entry_name);
} // namespace Database

#endif
