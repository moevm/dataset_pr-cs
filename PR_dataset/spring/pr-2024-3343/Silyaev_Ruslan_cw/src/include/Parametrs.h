#ifndef PARAMETRS_H
#define PARAMETRS_H

#include "main.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Parametrs* initParametrs(Parametrs* par);
void Help();
void Info(Png* image);
char** toCorrect(char* opt, int size);
Parametrs* CLI(int argc, char** argv);

#endif