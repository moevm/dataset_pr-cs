#ifndef CHECKERS_H
#define CHECKERS_H

#include "structs.h"

void coordschecker(char * coords);

void distancechecker(char * distance);

void colorchecker(char *color);

void thickchecker(char *thickness);

void nameschecker(char* inputname, char* outputname);

void bmp_namechecker(char * name);

void count_argscheck(char * first,char * second,char * third, char * name);

void no_argschecker(char* arg,char *name);

#endif