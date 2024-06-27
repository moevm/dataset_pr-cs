#include "replace_non_alfa_chars.h"

sentence *get_sentence_code_from_whchar(wchar_t ch)
{
    sentence *scode = create_sentence();
    swprintf(scode->text, scode->capacity, L"%ld", ch);
    scode->length = wcslen(scode->text);
    // wprintf(L"char: >%lc<\tcode: >%ls<\tlen: %d\n", ch, scode->text, scode->length);
    return scode;
}

void replace_non_alfa_chars_sentence(sentence *str)
{
    for (int i = 0; i < wcslen(str->text); i++)
    {
        if (iswalpha(str->text[i]))
            continue;

        sentence *scode = get_sentence_code_from_whchar(str->text[i]);
        str->length += scode->length - 1;
        enlarge_sentence_if_needed(str);
        wmemcpy(str->text + i + scode->length, str->text + i + 1, str->length - i);
        wmemcpy(str->text + i, scode->text, scode->length);
        i += scode->length - 1;
        free_sentence(scode);
    }
}

void replace_non_alfa_chars_text(text *txt)
{
    for (int i = 0; i < txt->length; i++)
    {
        replace_non_alfa_chars_sentence(txt->sentences[i]);
    }
}
