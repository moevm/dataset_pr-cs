#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>

#include "mystruct.h"


#define OPTION "5.11"
#define NAME "Insaf"
#define SURNAME "Zakirov"
#define BLOCK 20

void printinfo();

void printhelp();

void printallocerror(char* func, char* var, char* alloctype);

void printerror(char* message);

void printtext(Text* result);

void printf1(int num, int diff);

int scancommand();

void scantext(Text* text);
