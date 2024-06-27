#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

#include "structs.h"
#include "memory.h"
#include "text_processing.h"

#define SENTENCE_SPLITTER '.'

int getCommand();
int getDigit();
Word getWord();
Sentence getSentence(int *nCounter);
Text getText();

#endif
