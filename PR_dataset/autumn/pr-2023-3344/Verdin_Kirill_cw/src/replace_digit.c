#include "replace_digit.h"

Word *get_name_digit(wchar_t ch)
{
    Word *name = make_word();
    switch (ch)
    {
    case L'0':
    {
        wcscat(name->chars, L"ноль");
        break;
    }
    case L'1':
    {
        wcscat(name->chars, L"один");
        break;
    }
    case L'2':
    {
        wcscat(name->chars, L"два");
        break;
    }
    case L'3':
    {
        wcscat(name->chars, L"три");
        break;
    }
    case L'4':
    {
        wcscat(name->chars, L"четыре");
        break;
    }
    case L'5':
    {
        wcscat(name->chars, L"пять");
        break;
    }
    case L'6':
    {
        wcscat(name->chars, L"шесть");
        break;
    }
    case L'7':
    {
        wcscat(name->chars, L"семь");
        break;
    }
    case L'8':
    {
        wcscat(name->chars, L"восемь");
        break;
    }
    case L'9':
    {
        wcscat(name->chars, L"девять");
        break;
    }
    default:
    {
        return NULL;
    }
    }
    name->length = wcslen(name->chars);
    return name;
}

void replace_digit(Word *word)
{
    
    Word *name = get_name_digit(word->chars[wcslen(word->chars) - 1]);
    if (name)
    {
        Word *name = get_name_digit(word->chars[wcslen(word->chars) - 1]);
        word->length += name->length - 1;
        if (word->capacity_chars <= word->length - 2)
        {
            expand_word(word);
        }
        wmemcpy(word->chars + wcslen(word->chars) + name->length - 1, word->chars + wcslen(word->chars), 1);
        wmemcpy(word->chars + wcslen(word->chars) - 1, name->chars, name->length);
    }
    free_word(name);
}

void replace_digit_in_sentence(Sentence *str)
{
    for (size_t i = 0; i < str->count_words; i++)
    {
        replace_digit(str->array_of_words[i]);
    }
}

void replace_digit_in_text(Text *txt)
{
    for (size_t i = 0; i < txt->length; i++)
    {
        replace_digit_in_sentence(txt->array_sentence[i]);
    }
}