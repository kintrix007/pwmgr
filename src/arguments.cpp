#include "src/arguments.h"

Args::Command::~Command() { delete this->flags; }

Args::FlagsUnion::~FlagsUnion() {}

const Args::Command Args::parse(int argc, char **argv) {
  FlagsUnion *flags = new FlagsUnion{};

  // // flags->help = {"help"};
  // flags->help = {{}};
  // Args::Command command = {HELP, flags};
  flags->list = {{USERNAME, WEBSITE}};
  // flags->list = {{NAME}};
  Args::Command command = {LIST, flags};

  return command;
}
