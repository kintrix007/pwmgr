#include "src/arguments.h"
#include <iostream>
#include <string>

Args::Command::~Command() { delete this->flags; }

Args::FlagsUnion::FlagsUnion() {
    this->help = nullptr;
}

Args::FlagsUnion::~FlagsUnion() {}

//TODO: Implement parsing
const Args::Command Args::parse(int argc, char **argv) {
  FlagsUnion *flags = new FlagsUnion{};

  // // flags->help = {"help"};
  // flags->help = {{}};
  // Args::Command command = {HELP, flags};

  // flags->list = {{USERNAME, WEBSITE, NAME}};
  // Args::Command command = {LIST, flags};

  // flags->add = {true, {16, true, false, false, false}};
  // Args::Command command = {ADD, flags};

  // flags->remove = {{"a", "b"}};
  // Args::Command command = {REMOVE, flags};

  // flags->edit = new EditFlags{"b"};
  // Args::Command command = {EDIT, flags};

  flags->search = new SearchFlags{NAME, "name"};
  Args::Command command = {SEARCH, flags};

  return command;
}
