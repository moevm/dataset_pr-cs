#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include "../include/delete_equal_words.h"

char **deleteEqualLenWords(char **init_sentences, int *count) //удаляет предложения, если все слова имеют одинаковую длину
{
    char **sentences = (char **)malloc(sizeof(char *));
    int idx2 = 0;
    for (int i = 0; i < *count; i++)
    {
        int *len_words = (int *)malloc(sizeof(int));
        int idx1 = 0;
        char *res_sentence = strdup(init_sentences[i]);
        char *word = strtok(init_sentences[i], ", .\n\t\r\v\f");
        while (word != NULL)
        {
            len_words[idx1++] = strlen(word);
            len_words = realloc(len_words, (idx1 + 1) * sizeof(int));
            word = strtok(NULL, ", .\n\t\r\v\f");
        }
        if (idx1 == 1)
        {
            free(init_sentences[i]);
            continue;
        }
        int flag = 0;
        for (int j = 1; j < idx1; j++)
        {
            if (len_words[0] != len_words[j])
            {
                flag = 1;
                break;
            }
        }
        free(len_words);
        if (flag)
        {
            sentences[idx2++] = res_sentence;
            sentences = realloc(sentences, (idx2 + 1) * sizeof(char *));
        }
        else
        {
            free(init_sentences[i]);
        }
    }
    *count = idx2;
    return sentences;
}