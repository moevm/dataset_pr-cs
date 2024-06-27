#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_text.h"
#include "remove_duplicate_sentences.h"

int compare_sentences(Sentence str1, Sentence str2)
{
    if (strcmp(str1.sentence, str2.sentence) == 0)
    {
        return 1;
    }
    return 0;
}

Text remove_duplicate_sentences(Text text)
{
    int num_duplicates = 0;
    int *duplicate_indices = (int *)malloc(text.sentence_count * sizeof(int));

    for (int i = 0; i < text.sentence_count; i++)
    {
        for (int j = i + 1; j < text.sentence_count; j++)
        {
            if (compare_sentences(text.sentences[i], text.sentences[j]))
            {
                duplicate_indices[num_duplicates] = j;
                num_duplicates++;
                break;
            }
        }
    }

    Text filter_text;
    filter_text.sentences = malloc((text.sentence_count - num_duplicates) * sizeof(Sentence));
    filter_text.sentence_count = 0;

    for (int i = 0; i < text.sentence_count; i++)
    {
        int is_duplicate = 0;
        for (int j = 0; j < num_duplicates; j++)
        {
            if (i == duplicate_indices[j])
            {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate)
        {
            int length = strlen(text.sentences[i].sentence) + 1;
            filter_text.sentences[filter_text.sentence_count].sentence = (char *)malloc(length * sizeof(char));
            strcpy(filter_text.sentences[filter_text.sentence_count].sentence, text.sentences[i].sentence);
            filter_text.sentence_count++;
        }
    }

    free(duplicate_indices);
    return filter_text;
}

