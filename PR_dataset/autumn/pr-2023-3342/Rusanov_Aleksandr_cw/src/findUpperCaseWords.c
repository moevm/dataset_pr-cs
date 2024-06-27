#include "findUpperCaseWords.h"

int contains_word_in_sentence(Sentence *sentence, wchar_t *word)
{
    wchar_t *was_found = wcsstr(sentence->string, word);
    if (was_found == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int *find_indexes(Text text, wchar_t *word, int *cnt)
{
    int *indexes = (int *)calloc(text.size, sizeof(int));
    int size = 0;
    for (size_t i = 0; i < text.size; i++)
    {
        if (contains_word_in_sentence(&(text.sentences[i]), word))
        {
            indexes[size++] = i;
        }
    }
    indexes = (int *)realloc(indexes, size);
    *cnt = size;
    return indexes;
}

int is_unique(wchar_t *word, int amount_of_words, wchar_t *found_words)
{
    for (size_t j = 0; j < amount_of_words; j++)
    {
        if (wcscmp(word, found_words[j]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void print_found_words(Text text, int amount_of_words, wchar_t *found_words)
{
    for (size_t index_of_word = 0; index_of_word < amount_of_words; index_of_word++)
    {
        int cnt = 0;
        int *indexes = find_indexes(text, found_words[index_of_word], &cnt);
        wprintf(L"Слово \"%S\" найдено в предложениях со следующими индексами: ", found_words[index_of_word]);
        for (size_t j = 0; j < cnt; j++)
        {
            wprintf(L"%d", indexes[j]);
            if (cnt - 1 != j)
            {
                wprintf(L", ");
            }
            else
            {
                wprintf(L".");
            }
        }
        wprintf(L"\n");

        free(found_words[index_of_word]);
        free(indexes);
    }
    free(found_words);
}

void find_word_usage(Text text)
{
    int buffer = CHUNK;
    int amount_of_words = 0;
    wchar_t **found_words = (wchar_t **)malloc(buffer * sizeof(wchar_t *));

    int start_index = 0;
    int end_index = 0;
    int flag = 0;

    for (size_t index_of_sentence = 0; index_of_sentence < text.size; index_of_sentence++)
    {
        for (int index = 0; index < text.sentences[index_of_sentence].size; index++)
        {
            if (flag == 0 && !is_separator(text.sentences[index_of_sentence].string[index]))
            {
                flag = 1;
                start_index = index;
            }

            if (flag == 1 && is_separator(text.sentences[index_of_sentence].string[index]))
            {
                end_index = index;

                int word_length = end_index - start_index;
                wchar_t *word = (wchar_t *)calloc((word_length + 1), sizeof(wchar_t));
                for (size_t i = 0; i < word_length; i++)
                {
                    word[i] = text.sentences[index_of_sentence].string[start_index + i];
                }
                word[word_length] = '\0';

                if (iswupper(word[word_length - 1]) && iswupper(word[0]))
                {

                    if (is_unique(word, amount_of_words, found_words))
                    {
                        if (amount_of_words == buffer)
                        {
                            buffer += CHUNK;
                            found_words = (wchar_t **)realloc(found_words, CHUNK * sizeof(wchar_t *));
                        }
                        wchar_t *copy_of_word = wcsdup(word);
                        found_words[amount_of_words++] = copy_of_word;
                    }
                }
                free(word);
                flag = 0;
            }
        }
    }

    print_found_words(text, amount_of_words, found_words);
}
