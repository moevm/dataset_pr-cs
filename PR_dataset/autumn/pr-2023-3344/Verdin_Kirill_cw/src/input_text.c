#include <stdlib.h>
#include "input_text.h"

int is_sep(wchar_t ch)
{

    if (ch != L'\n' && ch != L' ' && ch != L'\t' && ch != L',')
    {
        return 0;
    }
    return 1;
}

Text *input_text()
{
    Text *txt = make_text();
    wchar_t *ch = (wchar_t *)malloc(sizeof(wchar_t));
    wchar_t previous_ch;
    int countn = 0;
    Sentence *sent;

    while (countn != 2)
    {
        sent = make_sentence();
        wchar_t previous_ch = L' ';
        wchar_t *word;
        wchar_t *sep;
        int c = 0;
        do
        {
            Word *word = make_word();
            Word *sep = make_word();
            do
            {
                if (previous_ch != L'\0')
                {
                    *ch = getwchar();
                }
                if ((*ch == L'.' || *ch == L' ' || *ch == L'\t' || *ch == L',') && word->length == 0)
                    continue;
                if (previous_ch == L'\n' && *ch == L'\n')
                {
                    countn = 2;
                    continue;
                }
                if ((is_sep(previous_ch)) && (!is_sep(*ch)) || *ch == L'.')
                    break;
                if (is_sep(*ch))
                {
                    sep->length++;
                    if (sep->length >= sep->capacity_chars - 2)
                    {
                        expand_word(sep);
                    }
                    wcscat(sep->chars, ch);
                }
                else
                {
                    word->length++;
                    if (word->length >= word->capacity_chars - 2)
                    {
                        expand_word(word);
                    }
                    wcscat(word->chars, ch);
                }
                // wprintf(L"%ls %d %lc %lc\n", word, count_ch_sep, previous_ch, *ch);
                previous_ch = *ch;
            } while (1);
            wchar_t *ch = (wchar_t *)malloc(sizeof(wchar_t));
            previous_ch = L'\0';
            if (word->length)
            {

                sent->array_of_words[sent->count_words++] = word;
                expand_array_words(sent);

                sent->array_of_sep[sent->count_sep++] = sep;
                expand_array_sep(sent);
            }
        } while (*ch != L'.' && countn != 2);
        if (sentence_is_in_text(txt->array_sentence, sent, txt->length) && sent->count_words != 0)
        {
            txt->array_sentence[txt->length] = sent;
            txt->length += 1;
            expand_text(txt);
        }
        // wprintf(L"%dДлинна\n", txt->length);
    }
    return txt;
}