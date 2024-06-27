#ifndef SPLITTEDSENTENCE_H
#define SPLITTEDSENTENCE_H


#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#include "struct.h"

wchar_t** splitSentence(Sentence sentence, int* count);

#endif