#include "src/generator.h"
#include <iostream>
#include <string>

int main() {
  srand((unsigned)time(NULL));

  Password::Options opts = {
      .length = 30,
      .upper = false,
      .lower = false,
      .numbers = true,
      .symbols = false,
  };

  // std::optional<int> my_opt = 1;
  // auto x = my_opt.transform([](int x){ return x+2; });
  // std::cout << "Has value: " << x.value() << std::endl;

  std::string password = Password::generate(opts);
  std::cout << password << std::endl;

  return 0;
}
