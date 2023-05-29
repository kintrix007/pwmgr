#ifndef COMMAND_ADD_H
#define COMMAND_ADD_H

#include "src/arguments.h"
#include "src/database.h"

namespace Add {
void run(Database::DB *db, Args::AddFlags flags);
}

#endif
