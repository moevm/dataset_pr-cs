#pragma once
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <time.h>

struct Sentence * get_sentence();
struct Text * get_text();
wchar_t ** get_words(struct Sentence * sentence);
void print_text(struct Text * text);
