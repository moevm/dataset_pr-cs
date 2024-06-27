#include "replace_words.h"
#include <wchar.h>

sentence *get_bslovo_sentence()
{
    sentence *bslovo = create_sentence();
    swprintf(bslovo->text, bslovo->capacity, L"(большое слово)");
    bslovo->length = wcslen(bslovo->text);
    // wprintf(L"char: >%lc<\tcode: >%ls<\tlen: %d\n", ch, scode->text, scode->length);
    return bslovo;
}

// void replace_non_sentence(sentence *str)
// {
//     for (int i = 0; i < wcslen(str->text); i++)
//     {
//         if (iswalpha(str->text[i]))
//             continue;

//         sentence *scode = get_sentence_from_whchar(str->text[i]);
//         str->length += scode->length - 1;
//         enlarge_sentence_if_needed(str);
//         wmemcpy(str->text + i + scode->length, str->text + i + 1, str->length - i);
//         wmemcpy(str->text + i, scode->text, scode->length);
//         i += scode->length - 1;
//         free_sentence(scode);
//     }
// }

void replace_words(text *txt, int first_length)
{
    for (int i = 0; i < txt->length; i++)
    {
        sentence *str = txt->sentences[i];
        sentence *temp = create_sentence();
        append_wchar_to_sentence(temp, str->text);

        wchar_t *safe;
        wchar_t *token = wcstok(temp->text, L" ,", &safe);
        int shift = 0;
        int j = 0;
        // wprintf(L"%d\n", first_length);
        while (token != NULL)
        {
            // print_sentence(temp, 1);
            sentence *word = create_sentence();
            append_wchar_to_sentence(word, token);

            // wprintf(L"%d\n", token - temp->text);
            j = (token - temp->text) + shift;
            if (word->length <= first_length)
            {
                token = wcstok(NULL, L" ,", &safe);
                // wprintf(L"%d\n", token - temp->text);
                // shift += word->length;
                continue;
            }

            sentence *bslovo = get_bslovo_sentence();
            str->length += bslovo->length - word->length;
            enlarge_sentence_if_needed(str);
            // wprintf(L"%ls \n", word->text);

            // wprintf(L"%d %d %d %d %ls %D\n", str->length, word->length, j, shift, str->text + j + word->length, str->length - j - bslovo->length);
            if (str->length - j - bslovo->length)
                wmemcpy(str->text + j + bslovo->length, str->text + j + word->length, str->length - j - bslovo->length);
            // wmemcpy(str->text + j + bslovo->length, str->text + j + word->length, str->length - j - bslovo->length);
            wmemcpy(str->text + j, bslovo->text, bslovo->length);
            shift += bslovo->length - word->length;
            free_sentence(bslovo);
            token = wcstok(NULL, L" ,", &safe);
        }

        free_sentence(temp);
    }
}
