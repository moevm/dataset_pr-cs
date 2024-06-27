#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "read_text.h"
#include "remove_mixed_alphabet_sentences.h"

int has_mixed_alphabet(char *word)
{
    int len = strlen(word);
    int exist_latin = 0;
    int exist_cyrillic = 0;

    for (int i = 0; i < len; i++)
    {
        if (isdigit(word[i]))
        {
            continue;
        }
        if (isalpha(word[i]) && !isascii(word[i]))
        {
            exist_cyrillic = 1;
        }
        if (isascii(word[i]))
        {
            exist_latin = 1;
        }
        if (exist_cyrillic && exist_latin)
            break;
    }

    if (exist_cyrillic && exist_latin)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void remove_mixed_alphabet_sentences(Text text)
{
    Text new_text;
    new_text.sentences = malloc(text.sentence_count * sizeof(Sentence));
    new_text.sentence_count = 0;

    for (int i = 0; i < text.sentence_count; i++)
    {
        new_text.sentences[i].sentence = malloc((strlen(text.sentences[i].sentence) + 1) * sizeof(char));
        new_text.sentence_count++;
        strcpy(new_text.sentences[i].sentence, text.sentences[i].sentence);
    }

    for (int i = 0; i < new_text.sentence_count; i++)
    {
        trim(new_text.sentences[i]);
    }

    for (int i = 0; i < new_text.sentence_count; i++)
    {
        int exist_mixed = 0;
        char *sentence = new_text.sentences[i].sentence;

        char *word = strtok(sentence, " ,.");
        while (word != NULL)
        {
            if (has_mixed_alphabet(word))
            {
                exist_mixed = 1;
                break;
            }
            word = strtok(NULL, " ,.");
        }
        if (!exist_mixed)
        {
            printf("%s\n", text.sentences[i].sentence);
        }
    }

    for (int i = 0; i < new_text.sentence_count; i++)
    {
        free(new_text.sentences[i].sentence);
    }
    free(new_text.sentences);
}