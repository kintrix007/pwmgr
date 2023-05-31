#include "src/arguments.h"
#include <iostream>
#include <string>

Args::Command::~Command() { delete this->flags; }

Args::FlagsUnion::FlagsUnion() {
    this->help = nullptr;
}

Args::FlagsUnion::~FlagsUnion() {}

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

  flags->edit = new EditFlags{"b"}; // This segfaults... Absolutely no clue why.
  Args::Command command = {EDIT, flags};

  return command;
}
