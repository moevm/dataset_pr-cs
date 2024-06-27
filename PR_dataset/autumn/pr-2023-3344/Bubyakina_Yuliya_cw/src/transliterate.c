#include "transliterate.h"
#include "sentence.h"
#include "text.h"
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>

const wchar_t *find_GOST_replacement(wchar_t ch)
{
    switch (towupper(ch))
    {
    case L'А':
        return L"A";
    case L'Б':
        return L"B";
    case L'В':
        return L"V";
    case L'Г':
        return L"G";
    case L'Д':
        return L"D";
    case L'Е':
        return L"E";
    case L'Ё':
        return L"YO";
    case L'Ж':
        return L"ZH";
    case L'З':
        return L"Z";
    case L'И':
        return L"I";
    case L'Й':
        return L"J";
    case L'К':
        return L"K";
    case L'Л':
        return L"L";
    case L'М':
        return L"M";
    case L'Н':
        return L"N";
    case L'О':
        return L"O";
    case L'П':
        return L"P";
    case L'Р':
        return L"R";
    case L'С':
        return L"S";
    case L'Т':
        return L"T";
    case L'У':
        return L"U";
    case L'Ф':
        return L"F";
    case L'Х':
        return L"X";
    case L'Ц':
        return L"C";
    case L'Ч':
        return L"CH";
    case L'Ш':
        return L"SH";
    case L'Щ':
        return L"SHH";
    case L'Ъ':
        return L"’’";
    case L'Ы':
        return L"Y’";
    case L'Ь':
        return L"’";
    case L'Э':
        return L"E’";
    case L'Ю':
        return L"YU";
    case L'Я':
        return L"YA";

    default:
        return L"";
    }
}

void towlower_string(wchar_t **str)
{
    for (int k = 0; k < wcslen(*str); k++)
    {
        (*str)[k] = towlower((*str)[k]);
    }
}

void transliterate(Text *text)
{
    wchar_t *replacement = (wchar_t *)malloc(10 * sizeof(wchar_t));
    for (int i = 0; i < text->len; i++)
    {
        Sentence *sentence = text->sentences[i];
        for (int j = 0; j < sentence->len; j++)
        {
            wchar_t ch = sentence->chars[j];
            swprintf(replacement, 10, L"%ls", find_GOST_replacement(ch));
            int repl_len = wcslen(replacement);

            if (!repl_len)
                continue;

            if (iswlower(ch))
                towlower_string(&replacement);

            // wprintf(L"now: %lc %d\n", ch, repl_len);

            j += replace_n_at_index_sentence(sentence, replacement, 1, j);
        }
        // print_sentence(sentence);
    }
    free(replacement);
}
