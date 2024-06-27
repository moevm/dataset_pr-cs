#ifndef FUNC_PARAMS_H
#define FUNC_PARAMS_H

#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

OptParams* initOptParams(OptParams* opt);
void printHelp();
void printInfo(Png* image);
char** parseArgs(char* arg, int size);
OptParams* parseCommandLine(int argc, char** argv);

#endif