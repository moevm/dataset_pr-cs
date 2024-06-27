#pragma once
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <wctype.h>
#include "structs.h"
#include "other_stuff.h"

#define CYRILLIC_DICT {{L"А", L"A"}, {L"Б", L"B"}, {L"В",L"V"}, {L"Г",L"G"}, {L"Д", L"D"}, {L"Е", L"E"}, {L"Ё", L"YO"}, {L"Ж", L"Zh"}, {L"З", L"Z"}, {L"И", L"I"}, {L"Й", L"J"}, {L"К", L"K"}, {L"Л", L"L"}, {L"М", L"M"}, {L"Н", L"N"}, {L"О", L"O"}, {L"П", L"P"}, {L"Р", L"R"}, {L"С", L"S"}, {L"Т", L"T"}, {L"У", L"U"}, {L"Ф", L"F"}, {L"Х", L"H"}, {L"Ц", L"Cz"}, {L"Ч", L"Ch"}, {L"Ш", L"Sh"}, {L"Щ", L"Shh"}, {L"Ъ", L"``"}, {L"Ы", L"Y`"}, {L"Ь", L"`"}, {L"Э", L"E`"}, {L"Ю", L"Yu"}, {L"Я", L"Ya"}, {L"а", L"a"}, {L"б", L"b"}, {L"в", L"v"}, {L"г", L"g"}, {L"д", L"d"}, {L"е", L"e"}, {L"ё", L"yo"}, {L"ж", L"zh"}, {L"з", L"z"}, {L"и", L"i"}, {L"й", L"j"}, {L"к", L"k"}, {L"л", L"l"}, {L"м", L"m"}, {L"н", L"n"}, {L"о", L"o"}, {L"п", L"p"}, {L"р", L"r"}, {L"с", L"s"}, {L"т", L"t"}, {L"у", L"u"}, {L"ф", L"f"}, {L"х", L"h"}, {L"ц", L"cz"}, {L"ч", L"ch"}, {L"ш", L"sh"}, {L"щ", L"shh"}, {L"ъ", L"``"}, {L"ы", L"y`"}, {L"ь", L"`"}, {L"э", L"e`"}, {L"ю", L"yu"}, {L"я", L"ya"}}

struct Sentence *make_trans(struct Sentence *sentence);
struct Text translitiration(struct Text text);
void all_transliteration(struct Text text);
