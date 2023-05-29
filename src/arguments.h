#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <optional>
#include <string>
#include <vector>
namespace Args {
enum Mode { HELP, ADD, EDIT, REMOVE, SEARCH, LIST };
enum Field { NAME, CATEGORY, WEBSITE, USERNAME };

struct HelpFlags {
  std::optional<std::string> command;
};

struct AddFlags {
  bool gen_lower;
  bool gen_upper;
  bool gen_number;
  bool gen_symbol;
};

struct EditFlags {};

struct RemoveFlags {
  bool batch;
};

struct SearchFlags {
  Field search_on;
};

struct ListFlags {
  std::vector<Field> sort_on;
};

union FlagsUnion {
  HelpFlags help;
  AddFlags add;
  EditFlags edit;
  RemoveFlags remove;
  SearchFlags search;
  ListFlags list{{}};

  ~FlagsUnion();
};

struct Command {
  Mode mode;
  FlagsUnion *flags;
  ~Command();
};

const Command parse(int argc, char **argv);
} // namespace Args

#endif
