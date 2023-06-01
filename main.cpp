#include "src/arguments.h"
#include "src/commands.h"
#include "src/database.h"
#include "src/generator.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char **argv) {
  // Generate new random seed based on system time
  srand((unsigned)time(NULL));

  // Password::Options opts = {
  //     .length = 30,
  //     .upper = false,
  //     .lower = false,
  //     .numbers = true,
  //     .symbols = false,
  // };

  auto command = Args::parse(argc, argv);

  Database::DB *db = new Database::DB;
  
  //TODO: Implement decryption
  std::ifstream in("test.db");
  in >> db;
  in.close();
  
  // Database::add_password(db, Database::new_entry (
  //       "new password",
  //       "um actually...",
  //       0, "asd", "bar"
  //       ));
  //
  // std::cout << Database::entry_exists(db, "name") << std::endl;
  // std::cout << Database::entry_exists(db, "name2") << std::endl;

  Commands::run(db, command);

  std::cout << db;

  //TODO: Implement encryption
  std::ofstream out("test.db");
  out << db;
  out.close();

  return 0;
}
