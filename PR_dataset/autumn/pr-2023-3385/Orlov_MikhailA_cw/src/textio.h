#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include "structs.h"

Sentence* ReadSentence(int* end);
Text* ReadText();
void PrintText(const Text* text);
void DeleteText(Text* text);