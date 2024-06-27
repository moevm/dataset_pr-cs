#ifndef TEXT_PROCESSING_H 
#define TEXT_PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "struct.h"

Text createText();
void addSentence(Text* text, Sentence sentence);

Sentence readSentence();

void readText(Text* text);
void clearText(Text* text);

void printText(Text* text);
void freeText(Text* text);

#endif