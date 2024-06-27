#ifndef INPUT_H
#define INPUT_H

#include "struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

Sentence getSentence(int* count, int *task);
Text getText(int task);

#endif