#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <ctype.h>

#include "../include/delete_first_word.h"

char **deleteFirstWord(char **init_sentences, int *count) // удаляет первое слово, которое встретилось в тексте
{
    char **sentences = (char **)malloc(sizeof(char *));
    int temp = 0;
    for (int i = 0; i < *count; i++)
    {
        char *rest = init_sentences[i];
        char *str;
        strtok_r(rest, ", .\n\t\r\v\f", &str);
        if (*str == '\0')
        {
            free(init_sentences[i]);
            continue;
        }
        while (isspace(str[0]) || str[0] == ',')
            memmove(&str[0], &str[1], strlen(str));
        if (*str != '.')
        {
            char *sentence = strdup(str);
            sentences[temp++] = sentence;
            sentences = realloc(sentences, (temp + 1) * sizeof(char *));
            free(init_sentences[i]);
        }
        else
            free(init_sentences[i]);
    }
    *count = temp;
    return sentences;
}