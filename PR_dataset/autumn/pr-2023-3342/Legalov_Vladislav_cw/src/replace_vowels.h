#pragma once
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "structures.h"
#include "breaks_in_sentence.h"
#include "wchar_checks.h"




void replace_vowel_in_text(Text* text);
void replace_vowel_in_sentence(Sentence* sentence);
BreaksData* find_vowel_pos(Sentence* sentence);
