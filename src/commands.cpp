#include "commands.h"
#include "src/arguments.h"
#include "src/commands/add.h"
#include "src/commands/edit.h"
#include "src/commands/help.h"
#include "src/commands/list.h"
#include "src/commands/remove.h"
#include "src/commands/search.h"

void commands::run(Database::DB *db, const Args::Command &command) {
  switch (command.mode) {
    case Args::HELP:
      Help::run(db, command.flags->help);
      break;
    case Args::ADD:
        Add::run(db, command.flags->add);
      break;
    case Args::EDIT:
      Edit::run(db, command.flags->edit);
      break;
    case Args::REMOVE:
      Remove::run(db, command.flags->remove);
      break;
    case Args::SEARCH:
      Search::run(db, command.flags->search);
      break;
    case Args::LIST:
      List::run(db, command.flags->list);
      break;
  }
}

