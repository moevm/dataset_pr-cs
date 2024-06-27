#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define END_OF_INPUT "Fin.\n"
#define SIZE 250

char **get_text(int *number_of_sentences)
{
    int sentence_count = 0;
    char **text = malloc(sizeof(char *));
    char *sentence = malloc(sizeof(char) * SIZE);
    if (sentence == NULL)
    {
        printf("Memory allocation error!");
        exit(1);
    }
    while (fgets(sentence, SIZE, stdin))
    {
        if (strcmp(sentence, END_OF_INPUT) == 0)
        {
            break;
        }
        sentence_count++;
        text = realloc(text, sizeof(char *) * sentence_count);
        if (text == NULL)
        {
            printf("Memory allocation error!");
            exit(1);
        }
        text[sentence_count - 1] = strdup(sentence);
        free(sentence);
        sentence = malloc(sizeof(char) * SIZE);
        if (sentence == NULL)
        {
            printf("Memory allocation error!");
            exit(1);
        }
    }
    free(sentence);
    *number_of_sentences = sentence_count;
    return text;
}

void print_match(char *sentence, regmatch_t group_array[], int index_of_group)
{
    for (int k = group_array[index_of_group].rm_so; k < group_array[index_of_group].rm_eo; k++)
    {
        printf("%c", sentence[k]);
    }
}

void free_text(char **text, int sentence_count)
{
    for (int i = 0; i < sentence_count; i++)
    {
        free(text[i]);
    }
    free(text);
}

int main()
{
    char *regex_string = "([a-zA-Z]+://)?(www\\.)?([a-zA-Z0-9-]+(\\.[a-zA-Z0-9]+)+)/((\\w+/)*)([a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+))*\n$";
    size_t max_groups = 9;
    regex_t regex_compiled;
    regmatch_t group_array[max_groups];
    int rc;

    if (0 != (rc = regcomp(&regex_compiled, regex_string, REG_EXTENDED)))
    {
        printf("Error: can't compile regular expression. Code %d\n", rc);
        return 0;
    };

    int sentence_count = 0;
    char **text = get_text(&sentence_count);
    int flag = 1;

    for (int i = 0; i < sentence_count; i++)
    {
        if (regexec(&regex_compiled, text[i], max_groups, group_array, 0) == 0)
        {
            if (flag)
            {
                flag = 0;
            }
            else
            {
                printf("\n");
            }
            print_match(text[i], group_array, 3);
            printf(" - ");
            print_match(text[i], group_array, 7);
        }
    }
    free_text(text, sentence_count);
    regfree(&regex_compiled);
    return 0;
}