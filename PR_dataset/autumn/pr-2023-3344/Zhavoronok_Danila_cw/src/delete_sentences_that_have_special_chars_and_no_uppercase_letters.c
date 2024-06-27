#include "delete_sentences_that_have_special_chars_and_no_uppercase_letters.h"
#include <string.h>

int sentence_has_special_chars_and_no_uppercase_letters(sentence *str)
{
    int count_special = 0;
    int count_uppercase = 0;
    for (int i = 0; i < str->length; i++)
    {
        if (wcschr(L"#$^%@", str->text[i]))
            count_special++;
        if (iswupper(str->text[i]))
            count_uppercase++;
    }
    // print_sentence(str, 1);
    // printf("%d %d\n", count_special, count_uppercase);
    return count_special && !count_uppercase;
}

void delete_sentences_that_have_special_chars_and_no_uppercase_letters(text *txt)
{
    text *words = create_text();
    for (int i = 0; i < txt->length; i++)
    {
        sentence *str = txt->sentences[i];
        if (sentence_has_special_chars_and_no_uppercase_letters(str))
        {
            free_sentence(str);
            memmove(txt->sentences + i, txt->sentences + i + 1, (txt->length - i - 1) * sizeof(sentence *));
            txt->length--;
            i--;
        }
    }
}
