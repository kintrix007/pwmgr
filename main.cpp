#include "src/arguments.h"
#include "src/database.h"
#include "src/generator.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  srand((unsigned)time(NULL));

  auto command = Args::parse(argc, argv);

  Password::Options opts = {
      .length = 30,
      .upper = false,
      .lower = false,
      .numbers = true,
      .symbols = false,
  };

  Database::DB *db = new Database::DB;
  // Database::add_password(db, Database::new_entry (
  //       "new password",
  //       "um actually...",
  //       0, "asd", "bar"
  //       ));
  //
  // std::cout << Database::entry_exists(db, "name") << std::endl;
  // std::cout << Database::entry_exists(db, "name2") << std::endl;

  std::cin >> db;
  std::cout << db << std::endl;
  
  // std::cout << (*Database::get_entries(db)[0]->name) << std::endl;

  // std::string password = Password::generate(opts);
  // std::cout << password << std::endl;

  return 0;
}
