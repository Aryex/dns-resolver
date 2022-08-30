#include <iostream>

#include "project_config.h"

int main(int argc, char* argv[]) {
    if (PROJECT_VERSION_MAJOR == 1 and PROJECT_VERSION_MINOR == 0)
        exit( EXIT_SUCCESS );

    exit( EXIT_FAILURE );
}