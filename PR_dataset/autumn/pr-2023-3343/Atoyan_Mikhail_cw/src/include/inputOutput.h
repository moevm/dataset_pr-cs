#ifndef INPUTOUTPUT_H
#define INPUTOUTPUT_H

#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>

#include "structures.h"

int get_command();
Text get_text();
void print_text(Text text);
Sentence get_sentence(int *nCounter);
wchar_t *get_word();
#endif //INPUTOUTPUT_H