#ifndef COMMAND_LINE_OPTIONS_OPERATIONS
#define COMMAND_LINE_OPTIONS_OPERATIONS

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "structs.h"


void printHelp();

RGB convertStringToRGB(char* color_string);

CommandLineOptions* initOptions();

CommandLineOptions* parseCommandLine(int argc, char* argv[]);


#endif
