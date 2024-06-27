#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Error-handling
#define MEMORY_ALLOC_ERROR 1
#define REGEX_COMPILE_FAILED 2

void my_error(int *err);

// Sentences
typedef struct
{
    size_t size;
    size_t memsize;
    char *sentence;
} Sentence;

#define SENTENCE_BUFFER 512
void regex_processing(int *err);
Sentence *sentence_read(int *err);
Sentence *sentence_create(int *err);
void sentence_delete(Sentence **sentence);
void sentence_add_symbol(Sentence *sentence, char symbol, int *err);

// Main
#define MAX_GROUPS 8
#define URL_PATTERN "([a-zA-Z]+:\\/\\/)?(www\\.)?(([a-zA-Z0-9_-]+\\.)+[a-zA-Z0-9_-]+)\\/(([a-zA-Z0-9_-]+\\/)*)([a-zA-Z0-9_-]*\\.[a-zA-Z0-9_-]+)"
#define DOMAIN_GROUP 3
#define FILE_GROUP 7
#define END_INPUT "Fin."

int main(void)
{
    int err = 0;
    regex_processing(&err);

    if (err != 0)
        return 1;

    return 0;
}

// processing sentences with regex
void regex_processing(int *err)
{
    regex_t regex;
    regmatch_t groups[MAX_GROUPS];

    if (regcomp(&regex, URL_PATTERN, REG_EXTENDED))
    {
        *err = REGEX_COMPILE_FAILED;
        regfree(&regex);
        my_error(err);
        return;
    }

    while (true)
    {
        Sentence *sentence = sentence_read(err);

        if (*err != 0)
        {
            sentence_delete(&sentence);
            regfree(&regex);
            my_error(err);
            return;
        }

        if (!strcmp(sentence->sentence, END_INPUT))
        {
            sentence_delete(&sentence);
            break;
        }

        if (regexec(&regex, sentence->sentence, MAX_GROUPS, groups, REG_EXTENDED) == 0)
        {
            // DOMAIN
            for (size_t i = groups[DOMAIN_GROUP].rm_so; i < groups[DOMAIN_GROUP].rm_eo; i++)
                printf("%c", sentence->sentence[i]);

            printf(" - ");
            // FILE
            for (size_t i = groups[FILE_GROUP].rm_so; i < groups[FILE_GROUP].rm_eo; i++)
                printf("%c", sentence->sentence[i]);
            printf("\n");
        }
        sentence_delete(&sentence);
    }
    regfree(&regex);
}

// Error information
void my_error(int *err)
{
    switch (*err)
    {
    case MEMORY_ALLOC_ERROR:
        printf("Error: Memory allocation error");
        break;
    case REGEX_COMPILE_FAILED:
        printf("Error: Regular cannot compile");
        break;
    }
}

// Create a sentence and read into it
Sentence *sentence_read(int *err)
{
    Sentence *sentence = sentence_create(err);
    if (*err != 0)
    {
        sentence_delete(&sentence);
        return NULL;
    }
    while (true)
    {
        char c = getchar();
        if (c != EOF && c != '\n')
            sentence_add_symbol(sentence, c, err);
        else
            sentence_add_symbol(sentence, '\0', err);

        if (*err != 0)
        {
            sentence_delete(&sentence);
            my_error(err);
            return NULL;
        }

        if (c == EOF || c == '\n')
            break;
    }
    return sentence;
}

// Constructor for sentences
Sentence *sentence_create(int *err)
{
    Sentence *new_sentence = malloc(sizeof(Sentence));
    if (new_sentence == NULL)
    {
        sentence_delete(&new_sentence);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }
    new_sentence->size = 0;
    new_sentence->memsize = SENTENCE_BUFFER;
    new_sentence->sentence = calloc(SENTENCE_BUFFER, sizeof(char));
    if (new_sentence->sentence == NULL)
    {
        sentence_delete(&new_sentence);
        *err = MEMORY_ALLOC_ERROR;
        return NULL;
    }
    return new_sentence;
}

// Destructor for sentences
void sentence_delete(Sentence **sentence)
{
    free((*sentence)->sentence);
    (*sentence)->sentence = NULL;
    free(*sentence);
    *sentence = NULL;
}

// Add symbol to sentence in the end
void sentence_add_symbol(Sentence *sentence, char symbol, int *err)
{
    if (sentence == NULL)
        return;
    if (*err)
        return;

    if (sentence->size >= sentence->memsize)
    {
        sentence->memsize += SENTENCE_BUFFER;
        sentence->sentence = realloc(sentence->sentence, sentence->memsize * sizeof(char));
        if (sentence->sentence == NULL)
        {
            sentence_delete(&sentence);
            *err = MEMORY_ALLOC_ERROR;
            return;
        }
    }
    sentence->sentence[sentence->size] = symbol;
    sentence->size++;
}