#include <iostream>

#include "my_library.h"

int initialize() {
    std::cout << "my_library is initiated\n";
    return 1;
}

int terminate() {
    std::cout << "my_library is terminated\n";
    return 1;
}
