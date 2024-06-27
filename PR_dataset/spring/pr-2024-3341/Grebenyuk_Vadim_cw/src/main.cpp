#include "Arguments/Arguments.h"
#include <png.h>
#include <iostream>

#define GREETING "Course work for option 4.24, created by Vadim Grebenyuk.\n"

int main(int argc, char *argv[]) {
    std::cout << GREETING;
    Arguments args(argc, argv);
    args.process();
    return 0;
}

