#ifndef DATABASE_H
#define DATABASE_H

#include <cstdint>
#include <string>
#include <optional>
#include <functional>

namespace Database {
    struct Entry {
        std::string name;
        std::string password;
        uint64_t category;
        std::optional<std::string> website;
    };
}

#endif
