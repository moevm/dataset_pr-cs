#define RED L"\033[4;31m"
#define NONE L"\033[0m"

#include "print_if_last_word_of_previous_sentence_is_in_current_sentence.h"

int is_last_word_in_sentence(Word *word, Sentence *str2)
{
    for (size_t i = 0; i < str2->count_words; i++)
    {
        if (wcscmp(word->chars, str2->array_of_words[i]->chars) == 0)
            return 1;
    }
    return 0;
}

void print_sentences_if_last_word_of_previous_sentence_is_in_current_sentence(Text *txt)
{
    for (size_t i = 0; i < (txt->length); i++)
    {
        Word *last_word;
        if (i == 0)
        {
            last_word = txt->array_sentence[txt->length - 1]->array_of_words[txt->array_sentence[txt->length - 1]->count_words - 1];
        }
        else
        {
            last_word = txt->array_sentence[i - 1]->array_of_words[txt->array_sentence[i - 1]->count_words - 1];
        }
        Sentence *current_sentence = txt->array_sentence[i];
        if (is_last_word_in_sentence(last_word, current_sentence))
        {
            for (size_t j = 0; j < current_sentence->count_words; j++)
            {
                Word *current_word = current_sentence->array_of_words[j];
                if (wcscmp(current_word->chars, last_word->chars) == 0)
                {
                    wprintf(L"%ls%ls%ls", RED, current_sentence->array_of_words[j]->chars, NONE);
                }
                else
                {
                    wprintf(L"%ls", current_sentence->array_of_words[j]->chars);
                }
                if (j < (current_sentence->count_sep))
                {
                    wprintf(L"%ls", current_sentence->array_of_sep[j]->chars);
                }
            }
            wprintf(L".\n");
        }
    }
}