#include "../include/throw_exception.h"

void throw_exception(std::string error, int exitCode)
{
    std::cerr << error << '\n';
    exit(exitCode);
}
