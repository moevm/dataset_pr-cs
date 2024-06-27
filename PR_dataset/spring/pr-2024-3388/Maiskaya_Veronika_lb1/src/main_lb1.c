#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BUFFER 100
#define REGEX "([A-Za-z0-9_]{1,})@[A-Za-z0-9_-]{1,}:\\s{0,}~\\s{0,}# (.{1,})"

void defineSize(char ***strings, int currentBufferSize)
{
    (*strings) = (char **)malloc(currentBufferSize * sizeof(char *));
    (*strings)[0] = (char *)malloc((BUFFER + 1) * sizeof(char));
}

void freeMemory(char ***strings, int stringNum)
{
    for (int i = 0; i <= stringNum; i++)
    {
        free((*strings)[i]);
    }
    free(*strings);
}

void inputStrings(char ***strings, int *stringNum, size_t *currentBufferSize)
{
    while (1)
    {
        if ((*stringNum) >= (*currentBufferSize))
        {
            (*currentBufferSize) *= 2;
            (*strings) = (char **)realloc((*strings), (*currentBufferSize) * sizeof(char *));
        }

        (*strings)[*stringNum] = (char *)malloc((BUFFER + 1) * sizeof(char));

        if (fgets((*strings)[*stringNum], BUFFER + 1, stdin) == NULL)
        {
            fprintf(stderr, "Error reading input\n");
            freeMemory(strings, *stringNum);
            exit(1);
        }

        size_t len = strlen((*strings)[*stringNum]);
        if (len > 0 && (*strings)[*stringNum][len - 1] == '\n')
            (*strings)[*stringNum][len - 1] = '\0';

        if (strcmp("Fin.", (*strings)[*stringNum]) == 0)
            break;

        (*stringNum)++;
    }
}

void printResult(char ***strings, int stringNum)
{
    char *regexString = REGEX;
    size_t maxGroups = 3;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        fprintf(stderr, "Cannot compile regular expression\n");
        freeMemory(strings, stringNum);
        exit(1);
    }

    for (int i = 0; i < stringNum; i++)
    {
        if (regexec(&regexCompiled, (*strings)[i], maxGroups, groupArray, 0) == 0)
        {
            printf("%.*s - %.*s\n",
                   (int)(groupArray[1].rm_eo - groupArray[1].rm_so), (*strings)[i] + groupArray[1].rm_so,
                   (int)(groupArray[2].rm_eo - groupArray[2].rm_so), (*strings)[i] + groupArray[2].rm_so);
        }
    }

    regfree(&regexCompiled);
}

int main()
{
    char **strings = NULL;
    int stringNum = 0;
    size_t currentBufferSize = BUFFER;

    defineSize(&strings, currentBufferSize);
    inputStrings(&strings, &stringNum, &currentBufferSize);
    printResult(&strings, stringNum);
    freeMemory(&strings, stringNum);

    return 0;
}

