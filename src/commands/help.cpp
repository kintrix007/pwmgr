#include "help.h"
#include "src/arguments.h"
#include <iostream>
#include <string>

static const char *help = R"EOF(
pwmgr <command>

Usage:

pwmgr help                                display this help sheet
pwmgr help <command>                      get help with a given command
pwmgr add [generator options...]          add a new password entry
pwmgr edit <name of the entry>            edit a pre-existing entry
pwmgr delete <names of entries...>        delete an existing entry
pwmgr search [search options...] <term>   search the database for entries
pwmgr list [sort options...]              list all entries in a sorted fashion

For more information on the commands run:
  pwmgr help <command>
For example:
  pwmgr help add

Environmental variables:
(To be implemented)

PWMGR_DB_FILE  -  path to the database file
  Sets the path to the database file that should be used.
  For example:
    PWMGR_DB_FILE=~/.local/share/pwmgr/passw.db pwmgr list
)EOF";

void Help::run(Database::DB *, const Args::HelpFlags &flags) {
  if (!flags.command.has_value()) {
    std::cout << help << std::endl;
    return;
  }

  auto command = flags.command.value();
  std::cout << "No help page available for '" << command << "' yet."
            << std::endl;
}
