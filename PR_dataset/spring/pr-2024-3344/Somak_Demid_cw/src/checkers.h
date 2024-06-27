#ifndef CHECKERS_H
#define CHECKERS_H

#include "structurs.h"

void coordschecker(char * cords);

void distancechecker(char * distance);

void colorchecker(char *color);

void thickchecker(char *thickness);

void nameschecker(char* inputname, char* outputname);

void count_argscheck(char * arg1,char * arg2,char * arg3, char * name);

void no_argschecker(char* arg1, char* arg2, char *name);

#endif