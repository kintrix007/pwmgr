#ifndef COMMANDS_H
#define COMMANDS_H

#include "src/arguments.h"
#include "src/database.h"
namespace Commands {
void run(Database::DB *db, const Args::Command &command);
}

#endif
