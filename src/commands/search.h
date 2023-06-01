#ifndef COMMAND_SEARCH_H
#define COMMAND_SEARCH_H

#include "src/arguments.h"
#include "src/database.h"

namespace Search {
void run(Database::DB *db, const Args::SearchFlags &flags);
}

#endif
