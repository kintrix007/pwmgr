#include "list.h"
#include "src/arguments.h"
#include "src/database.h"
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum Ord { LT, EQ, GT };

template <typename T> Ord compare(T x, T y) {
  if (x < y)
    return LT;
  if (x > y)
    return GT;
  return EQ;
}

std::function<bool(const Database::Entry *, const Database::Entry *)>
combine(const std::vector<std::function<Ord(const Database::Entry *,
                                            const Database::Entry *)>> &funcs) {
  return [&funcs](const Database::Entry *x, const Database::Entry *y) {
    for (auto f : funcs) {
      auto ord = f(x, y);

      switch (ord) {
      case LT:
        return true;
      case GT:
        return false;
      case EQ:
        continue;
      }
    }

    return false;
  };
}

std::function<Ord(const Database::Entry *, const Database::Entry *)>
field_to_cmp_func(const Args::Field field) {
  switch (field) {
  case Args::NAME:
    return [](auto x, auto y) { return compare(*x->name, *y->name); };
  case Args::CATEGORY:
    return [](auto x, auto y) { return compare(x->category, y->category); };
  case Args::WEBSITE:
    return [](auto x, auto y) { return compare(*x->website, *y->website); };
  case Args::USERNAME:
    return [](auto x, auto y) { return compare(*x->username, *y->username); };
  }
  throw; // Just to silence a warning
}

void List::run(Database::DB *db, Args::ListFlags flags) {
  auto entries = Database::get_entries(db);

  std::vector<
      std::function<Ord(const Database::Entry *, const Database::Entry *)>>
      cmp_funcs{};

  for (auto field : flags.sort_on) {
    cmp_funcs.push_back(field_to_cmp_func(field));
  }

  auto sort_by_func = combine(cmp_funcs);

  std::sort(entries.begin(), entries.end(), sort_by_func);

  for (auto e : entries) {
    std::cout << Database::human_str(e) << std::endl;
  }
}
