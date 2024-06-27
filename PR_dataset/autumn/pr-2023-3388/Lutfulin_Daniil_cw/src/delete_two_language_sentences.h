#pragma once
#include "structs.h"
#include <stdbool.h>
#include <stdlib.h>
#include "leave.h"
#define LATIN_CHARS L"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
#define CYRILLIC_CHARS L"йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ"

bool check_two_language_sentence(Sentence*);
Text *delete_two_language_sentences(Text*);