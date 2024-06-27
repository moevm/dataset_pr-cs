#include <iostream>
#include "help.hpp"

void printHelp() {
    std::cout << "--mirror                  Reflection of a given area" << std::endl;
    std::cout << "--copy                    Copying a given area" << std::endl;
    std::cout << "--color_replace           Replacing all pixels of one given color with another color" << std::endl;
    std::cout << "--split                   Splitting an image into N*M parts" << std::endl;
}
