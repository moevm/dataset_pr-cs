#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int match(char *string, char *pattern, regex_t *re, regmatch_t matchptr[], size_t nmatch)
{
    int s;
    s = regcomp(re, pattern, REG_EXTENDED);
    if (s != 0) {
        return s;
    }
    s = regexec(re, string, nmatch, matchptr, 0);
    return s;
}

void print_matched_substring(char *string, regmatch_t match)
{
    for (int i = match.rm_so; i < match.rm_eo; i++) {
        printf("%c", string[i]);
    }
}

int main()
{
    regex_t re;
    regmatch_t matchptr[9];
    int retval;
    char *pattern = "([a-zA-Z]+://)?(www\\.)?([a-zA-Z0-9-]+(\\.[a-zA-Z0-9]+)+)/((\\w+/)*)([a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+))*\n$";
    int sentence_counter = 0;
    char **text = malloc(sizeof(char *));
    char *sentence = malloc(sizeof(char) * 1000);

    if (text == NULL || sentence == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    while (fgets(sentence, 1000, stdin))
    {
        if (strcmp(sentence, "Fin.\n") == 0)
        {
            break;
        }
        sentence_counter++;
        char **temp_text = realloc(text, sizeof(char *) * sentence_counter);
        if (temp_text == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(sentence);
            free(text);
            return 1;
        }
        text = temp_text;
        text[sentence_counter - 1] = strdup(sentence);
        if (text[sentence_counter - 1] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            free(sentence);
            for (int i = 0; i < sentence_counter - 1; i++) {
                free(text[i]);
            }
            free(text);
            return 1;
        }
        sentence = malloc(sizeof(char) * 1000);
        if (sentence == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int i = 0; i < sentence_counter; i++) {
                free(text[i]);
            }
            free(text);
            return 1;
        }
    }

    for (int i = 0; i < sentence_counter; i++)
    {
        retval = match(text[i], pattern, &re, matchptr, 9);
        if (retval == 0)
        {
            print_matched_substring(text[i], matchptr[3]);
            printf(" - ");
            print_matched_substring(text[i], matchptr[7]);
            if (i != sentence_counter -1){
                printf("\n");
            }
        }
    }
    regfree(&re);

    free(sentence);
    for (int i = 0; i < sentence_counter; i++) {
        free(text[i]);
    }
    free(text);

    return 0;
}
