#ifndef MASKS_H
#define MASKS_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#include "struct.h"
#include "splittedSentence.h"
#include "free.h"

int compare(const void* a, const void* b);
void findMask(Text text);

#endif