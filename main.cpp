#include <iostream>
#include <ostream>
#include <string>
#include "src/generator.h"

int main() {
    srand((unsigned) time(NULL));

    Password::Options opts = {
        .length = 12,
        .upper = true, .lower = true,
        .numbers = true, .symbols = false,
    };

    std::string password = Password::generate(opts);
    std::cout << password << std::endl;

    return 0;
}
