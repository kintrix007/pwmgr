#include "src/arguments.h"

Args::Command::~Command() { delete this->flags; }

Args::FlagsUnion::~FlagsUnion() {}

const Args::Command Args::parse(int argc, char **argv) {
  FlagsUnion *flags = new FlagsUnion{};
  flags->help = {"help"};
  Args::Command command = {HELP, flags};
  return command;
}
