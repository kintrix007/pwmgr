#ifndef COMMAND_HELP_H
#define COMMAND_HELP_H

#include "src/arguments.h"
#include "src/database.h"

namespace Help {
void run(Database::DB *db, const Args::HelpFlags &flags);
}

#endif
