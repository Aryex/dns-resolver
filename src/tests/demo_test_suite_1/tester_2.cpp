#include <iostream>
#include "my_library.h"

int main(int argc, char* argv[]) {
    if (initialize() && terminate()) exit (EXIT_SUCCESS );
    exit( EXIT_FAILURE );
}