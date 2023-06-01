#ifndef COMMAND_LIST_H
#define COMMAND_LIST_H

#include "src/arguments.h"
#include "src/database.h"

namespace List {
void run(Database::DB *db, const Args::ListFlags &flags);
}

#endif
