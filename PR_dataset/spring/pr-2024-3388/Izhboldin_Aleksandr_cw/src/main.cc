#include <iostream>
#include "libs/data_processing_lib/data_processing.h"

int main(int argc, char **argv) {
  try {
    Args args(argc, argv);
    data_processing(args);
  } catch (std::exception &ex) {
    std::cout << ex.what() << std::endl;
    return EXIT_FAIL;
  }
  return EXIT_SUCCESS;
}
