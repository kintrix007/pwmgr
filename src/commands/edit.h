#ifndef COMMAND_EDIT_H
#define COMMAND_EDIT_H

#include "src/arguments.h"
#include "src/database.h"

namespace Edit {
void run(Database::DB *db, Args::EditFlags flags);
}

#endif
