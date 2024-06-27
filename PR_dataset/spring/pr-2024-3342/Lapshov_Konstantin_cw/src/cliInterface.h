#pragma once

#include <getopt.h>
#include "structures.h"
#include "errors.h"

Option getCliFlagsInfo(int argc, char *argv[]);

Point getPointValue(char* string);
Point* getPointsValue(char* string);
RGB getRGBValue(char* string);
int getNonNegativeNumber(char* string);
void printHelp();