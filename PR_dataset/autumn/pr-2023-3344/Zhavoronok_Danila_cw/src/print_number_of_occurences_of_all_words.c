#include "print_number_of_occurences_of_all_words.h"

void print_number_of_occurences_of_all_words(text *txt)
{
    text *words = create_text();
    for (int i = 0; i < txt->length; i++)
    {
        sentence *temp = create_sentence();
        append_wchar_to_sentence(temp, txt->sentences[i]->text);
        // print_sentence(temp, 1);

        wchar_t *safe;
        // wchar_t *safe = (wchar_t *)malloc(sizeof(wchar_t));
        wchar_t *token = wcstok(temp->text, L" ", &safe);
        while (token != NULL)
        {
            // print_sentence(temp, 1);
            sentence *word = create_sentence();
            append_wchar_to_sentence(word, token);
            sentence *already_inputed_word = find_sentence_in_text(words, word, 1);
            if (already_inputed_word == NULL)
            {
                word->counter = 1;
                // wprintf(L"%ls\n", token);
                append_text(words, word);
            }
            else
            {
                already_inputed_word->counter++;
                free_sentence(word);
            }

            token = wcstok(NULL, L" ", &safe);
        }

        free_sentence(temp);
        //  //free(safe);
    }

    for (int i = 0; i < words->length; i++)
    {
        sentence *word = words->sentences[i];
        wprintf(L"%ls %d\n", word->text, word->counter);
    }

    free_text(words);
}
