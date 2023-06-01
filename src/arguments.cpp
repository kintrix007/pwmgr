#include "src/arguments.h"
#include <cstring>
#include <string>
#include <unordered_map>

Args::Command::~Command() { delete this->flags; }

Args::FlagsUnion::FlagsUnion() { this->help = nullptr; }

Args::FlagsUnion::~FlagsUnion() {}

static const std::unordered_map<std::string, Args::Mode> str_to_mode = {
    {"--help", Args::HELP}, {"help", Args::HELP},     {"add", Args::ADD},
    {"edit", Args::EDIT},   {"remove", Args::REMOVE}, {"search", Args::SEARCH},
    {"list", Args::LIST},
};

// TODO: Implement parsing
std::optional<Args::Command*> Args::parse(int argc, char **argv) {
  if (argc <= 1) {
    return {};
  }

  std::string command_string = argv[1];

  bool invalid_mode = str_to_mode.find(command_string) == str_to_mode.end();
  if (invalid_mode) {
    return {};
  }

  Mode mode = str_to_mode.at(command_string);
  argc -= 2;
  argv += 2;

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

  flags->search = new SearchFlags{NAME, "a"};
  auto command = new Command{SEARCH, flags};

  return {command};
}
