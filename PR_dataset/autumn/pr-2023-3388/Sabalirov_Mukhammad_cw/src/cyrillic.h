#pragma once
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "structs.h"
#include "ioroutine.h"
#include "dict.h"

#define MEM_ERROR L"Error: Failed to allocate memory\n"
#define INPUT_ERROR L"Error: Incorrect end of input\n"
#define CYRILLIC_COUNT 66
#define TRANSLIT_LEN 4
#define CYRILLIC L"АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя"
#define CYRILLIC_TRANSLIT {L"A", L"B", L"V", L"G", L"D", L"E", L"YO", L"ZH", L"Z", L"I", L"J", L"K", L"L", L"M", L"N", L"O", L"P", L"R", L"S", L"T", L"U", L"F", L"X", L"CZ", L"CH", L"SH", L"SHH", L"``", L"Y`", L"`", L"E`", L"YU", L"YA", L"a", L"b", L"v", L"g", L"d", L"e", L"yo", L"zh", L"z", L"i", L"j", L"k", L"l", L"m", L"n", L"o", L"p", L"r", L"s", L"t", L"u", L"f", L"x", L"cz", L"ch", L"sh", L"shh", L"``", L"y`", L"`", L"e`", L"yu", L"ya"}

bool is_cyrillic(wchar_t);
struct Dict* initial_cyrillic_dict();
struct Sentence* translit_sentence(struct Sentence*, struct Dict*);
struct Text* translit_text(struct Text*, struct Dict*);
