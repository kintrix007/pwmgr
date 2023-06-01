#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "src/generator.h"
#include <optional>
#include <string>
#include <vector>
namespace Args {
enum Mode { HELP, ADD, EDIT, REMOVE, SEARCH, LIST };
enum Field { NAME, CATEGORY, WEBSITE, USERNAME };

struct HelpFlags {
  std::optional<std::string> command{};
};

struct AddFlags {
  bool only_required{};
  Password::Options password{};
};

struct EditFlags {
  std::string entry_name{};
};

struct RemoveFlags {
  std::vector<std::string> entry_names{};
};

struct SearchFlags {
  Field search_on{};
  std::string search_term{};
};

struct ListFlags {
  std::vector<Field> sort_on{};
};

union FlagsUnion {
  HelpFlags *help;
  AddFlags *add;
  EditFlags *edit;
  RemoveFlags *remove;
  SearchFlags *search;
  ListFlags *list;

  FlagsUnion();
  ~FlagsUnion();
};

struct Command {
  Mode mode;
  FlagsUnion *flags;
  ~Command();
};

std::optional<Command*> parse(int argc, char **argv);
} // namespace Args

#endif
