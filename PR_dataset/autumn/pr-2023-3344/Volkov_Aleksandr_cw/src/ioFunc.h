#pragma once
#include "structures.h"

struct Sentence readSentence();
struct Text readText();
int removeRepeated(struct Text *text);
void printText(struct Text *text);
void freeText(struct Text *text);
