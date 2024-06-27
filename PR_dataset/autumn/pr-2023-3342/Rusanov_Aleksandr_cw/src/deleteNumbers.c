#include "deleteNumbers.h"

int is_number(const wchar_t *word)
{
    int length = wcslen(word);
    for (size_t i = 0; i < length; i++)
    {
        if (!iswdigit(word[i]))
        {
            return 0;
        }
    }

    return 1;
}

wchar_t *remove_numbers_from_sentence(Sentence sentence)
{
    wchar_t *new_string = (wchar_t *)malloc((sentence.size + 1) * sizeof(wchar_t));
    int new_index = 0;

    int start_index = 0;
    int end_index = 0;
    int word_started = 0;

    for (size_t index = 0; index < sentence.size; index++)
    {
        if (word_started == 0 && !is_separator(sentence.string[index]))
        {
            word_started = 1;
            start_index = index;
        }

        if (word_started == 1 && is_separator(sentence.string[index]))
        {
            end_index = index;
            int word_length = end_index - start_index;
            wchar_t *word = (wchar_t *)malloc((word_length + 1) * sizeof(wchar_t));
            for (size_t i = 0; i < word_length; i++)
            {
                word[i] = sentence.string[start_index + i];
            }
            word[word_length] = '\0';

            if (!is_number(word))
            {
                for (size_t j = 0; j < word_length; j++)
                {
                    new_string[new_index++] = word[j];
                }
            }
            free(word);

            word_started = 0;
        }

        if (word_started == 0 && is_separator(sentence.string[index]))
        {
            new_string[new_index++] = sentence.string[index];
        }
    }
    new_string[new_index] = '\0';
    return new_string;
}

void delete_numbers_from_text(Text text)
{
    for (size_t index_of_sentence = 0; index_of_sentence < text.size; index_of_sentence++)
    {
        wchar_t *new_string = remove_numbers_from_sentence(text.sentences[index_of_sentence]);
        free(text.sentences[index_of_sentence].string);
        text.sentences[index_of_sentence].string = new_string;
    }
}

