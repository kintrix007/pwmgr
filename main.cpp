#include "src/arguments.h"
#include "src/database.h"
#include "src/generator.h"
#include <fstream>
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
  
  std::ifstream in("test.db");
  in >> db;
  in.close();
  
  std::cout << db;

  // Database::add_password(db, Database::new_entry (
  //       "new password",
  //       "um actually...",
  //       0, "asd", "bar"
  //       ));
  //
  // std::cout << Database::entry_exists(db, "name") << std::endl;
  // std::cout << Database::entry_exists(db, "name2") << std::endl;

  // std::cout << (*Database::get_entries(db)[0]->name) << std::endl;

  // std::string password = Password::generate(opts);
  // std::cout << password << std::endl;
  std::ofstream out("test.db");
  out << db;
  out.close();

  return 0;
}
