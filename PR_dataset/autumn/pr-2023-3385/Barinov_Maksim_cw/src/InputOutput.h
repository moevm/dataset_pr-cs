#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <ctype.h>
#include "Struct.h"
#include "func.h"

#define size_block 50

struct Sentence* ReadSentence();
void OutSentence(struct Sentence* a);
void OutText(struct Text* text);
struct Text* ReadText();
