#include"Structs.h"
#include"UniqueWordsCount.h"
#include<wchar.h>
#include<stdlib.h>
struct Unique_Word* unique_words_count(struct Text text, int* unique_count)
{
    int words_count = 0;
    int unique_words_count = 0;
    wchar_t** words = (wchar_t**)malloc(1 * sizeof(wchar_t*));
    struct Unique_Word* unique_words = (struct Unique_Word*)malloc(sizeof(struct Unique_Word));

    for (size_t i = 0; i < text.sentences_count; i++)
    {
        for (size_t j = 0; j < text.sentences[i].words_count; j++)
        {
            words = (wchar_t**)realloc(words, (words_count + 1) * sizeof(wchar_t*));
            words[words_count] = malloc((text.sentences[i].words[j].letters_count + 1) * sizeof(wchar_t));
            wcscpy(words[words_count], text.sentences[i].words[j].letters);
            if (words[words_count][text.sentences[i].words[j].letters_count - 1] == '.' || words[words_count][text.sentences[i].words[j].letters_count - 1] == ',')
            {
                words[words_count][text.sentences[i].words[j].letters_count - 1] = '\0';
            }

            words_count += 1;

        }
    }
    for (int i = 0; i < words_count; ++i)
    {
        int isUnique = 1;
        for (int j = 0; j < unique_words_count; ++j)
        {
            if (!wcscmp(unique_words[j].letters, words[i]))
            {
                isUnique = 0;
            }
        }
        if (isUnique)
        {
            unique_words = (struct Unique_Word*)realloc(unique_words, (unique_words_count + 1) * sizeof(struct Unique_Word));
            unique_words[unique_words_count].letters = (wchar_t*)malloc((wcslen(words[i]) + 1) * sizeof(wchar_t));
            wcscpy(unique_words[unique_words_count].letters, words[i]);
            unique_words_count++;

        }
    }

    for (int i = 0; i < unique_words_count; ++i)
    {
        unique_words[i].words_count = 0;
        for (int j = 0; j < words_count; ++j)
        {
            if (!wcscmp(unique_words[i].letters, words[j]))
            {
                unique_words[i].words_count++;
            }
        }
    }



    for (int i = 0; i < words_count; ++i)
    {
        free(words[i]);
    }
    free(words);


    *unique_count = unique_words_count;
    return unique_words;
}