#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_text.h"

void trim(Sentence sentence)
{
    int start = 0;
    int end = strlen(sentence.sentence) - 1;
    while (isspace(sentence.sentence[start]))
    {
        start++;
    }
    while (end >= start && isspace(sentence.sentence[end]))
    {
        end--;
    }
    int i;
    for (i = 0; i <= end - start; i++)
    {
        sentence.sentence[i] = sentence.sentence[start + i];
    }
    sentence.sentence[i] = '\0';
}

Text read_text()
{
    Text text;
    text.sentences = NULL;
    text.sentence_count = 0;
    char *input = malloc(1);
    int input_len = 0;
    char ch;
    char prev_ch = ' ';

    while ((ch = getchar()) != '\n' || prev_ch != '\n')
    {
        if (ch != '\n')
        {
            input[input_len] = ch;
            input_len++;
            input = realloc(input, (input_len + 1) * sizeof(char));
            input[input_len] = '\0';
        }
        prev_ch = ch;
    }

    if (!input_len)
    {
        puts("Error: no text entered.");
    }

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (input[i] == '.')
        {
            text.sentence_count++;
        }
    }

    text.sentences = malloc(text.sentence_count * sizeof(Sentence));

    char *start = input;
    char *point = strchr(input, '.');
    int counter = 0;

    while ((point != NULL))
    {
        text.sentences[counter].sentence = malloc((point - start + 2) * sizeof(char));
        strncpy(text.sentences[counter].sentence, start, point - start + 1);
        text.sentences[counter].sentence[point - start + 1] = '\0';
        counter++;

        start = point + 1;
        point = strchr(start, '.');
    }

    for (int i = 0; i < text.sentence_count; i++)
    {
        trim(text.sentences[i]);
    }

    free(input);

    return text;
}