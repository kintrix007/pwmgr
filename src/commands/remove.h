#ifndef COMMAND_REMOVE_H
#define COMMAND_REMOVE_H

#include "src/arguments.h"
#include "src/database.h"

namespace Remove {
void run(Database::DB *db, Args::RemoveFlags flags);
}

#endif
