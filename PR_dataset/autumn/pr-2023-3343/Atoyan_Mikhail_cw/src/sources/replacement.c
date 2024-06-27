#include "../include/replacement.h"

wchar_t *wcsistr(const wchar_t *String, const wchar_t *Pattern)
{
    wchar_t *pptr, *sptr, *start;

    for (start = (wchar_t *)String; *start != 0; ++start)
    {
        while (((*start != 0) && (towupper(*start) != towupper(*Pattern))))
        {
            ++start;
        }

        if (0 == *start)
            return NULL;

        pptr = (wchar_t *)Pattern;
        sptr = (wchar_t *)start;

        while (towupper(*sptr) == towupper(*pptr))
        {
            sptr++;
            pptr++;

            if (0 == *pptr)
                return (start);
        }
    }

    return NULL;
}

void replace_tsa(Sentence sentence)
{
    wchar_t *needle = L"тся";
    wchar_t *tsa = wcsistr(sentence.chars, needle);
    while (tsa != NULL)
    {
        if (iswlower(tsa[0]))
        {
            tsa[0] = '\n';
        }
        else
        {
            tsa[0] = '\t';
        }

        tsa = wcsistr(sentence.chars, needle);
    }
}

void replace_tsya(Sentence *sentence)
{
    wchar_t *needle = L"ться";

    wchar_t *newChars = (wchar_t *)malloc((sentence->size + 1) * sizeof(wchar_t));
    size_t newIndex = 0;
    wchar_t *tsya = wcsistr(sentence->chars, needle);
    for (size_t i = 0; i < sentence->size; ++i)
    {
        if (tsya == NULL)
        {
            newChars[newIndex++] = sentence->chars[i];
        }
        else
        {
            if (&(sentence->chars[i]) == &tsya[1])
            {
                tsya[1] = L'\n';
                tsya = wcsistr(sentence->chars, needle);
                continue;
            }
            newChars[newIndex++] = sentence->chars[i];;
        }
    }

    newChars[newIndex] = L'\0';
    free(sentence->chars);
    sentence->chars = newChars;
    sentence->size = wcslen(newChars);
}

void replace_tmp(Sentence *sentence)
{
    wchar_t *needleLower = L"\n";
    wchar_t *needleUpper = L"\t";
    wchar_t *newChars = (wchar_t *)malloc((sentence->size + sentence->amofwords + 1) * 2 * sizeof(wchar_t));

    size_t newIndex = 0;
    wchar_t *tsaLower = wcsistr(sentence->chars, needleLower);
    wchar_t *tsaUpper = wcsistr(sentence->chars, needleUpper);
    for (size_t i = 0; i < sentence->size; ++i)
    {
        if (tsaLower == NULL && tsaUpper == NULL)
        {
            newChars[newIndex++] = sentence->chars[i];
        }
        else
        {
            if (sentence->chars[i] == L'\n')
            {
                newChars[newIndex++] = L'т';
                newChars[newIndex++] = L'ь';
                sentence->chars[i] = L'т';
                tsaLower = wcsistr(sentence->chars, needleLower);
            }
            else if ((sentence->chars[i] == L'\t'))
            {
                newChars[newIndex++] = L'Т';
                newChars[newIndex++] = L'ь';
                sentence->chars[i] = L'Т';
                tsaUpper = wcsistr(sentence->chars, needleUpper);
            }
            else
            {
                newChars[newIndex++] = sentence->chars[i];
            }
        }
    }

    newChars[newIndex] = L'\0';

    free(sentence->chars);
    sentence->chars = newChars;
    sentence->size = wcslen(newChars);
}

Text replace_text(Text text)
{
    for (int i = 0; i < text.size; i++)
    {
        replace_tsa(text.sentences[i]);
        replace_tsya(&(text.sentences[i]));
        replace_tmp(&(text.sentences[i]));
    }
    return text;
}