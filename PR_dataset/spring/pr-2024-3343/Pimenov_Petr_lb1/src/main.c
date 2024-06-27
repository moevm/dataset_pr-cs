#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define MEMORY_BLOCK_SIZE 10
#define TEXT_END "Fin."
#define REGEX_STRING "([a-zA-Z]+:\\/\\/)?(www\\.)?(([a-zA-Z0-9.\\-])+\\.([a-zA-Z0-9])+)(\\/[a-zA-Z0-9_\\-]+)*\\/([a-zA-Z0-9_\\-]+\\.[a-zA-Z0-9]+)"

int main()
{
    size_t size = 0;
    size_t capacity = MEMORY_BLOCK_SIZE;
    char *text = (char *)malloc(capacity * sizeof(char));
    int last_char = getchar();
    if (last_char == '\0' || last_char == EOF)
    {
        return 0;
    }
    text[size++] = last_char;
    text[size] = '\0';
    last_char = getchar();
    while (last_char != '\0' && last_char != EOF)
    {
        text[size++] = last_char;
        text[size] = '\0';
        if (strstr(text, TEXT_END) != NULL)
        {
            break;
        }
        if (size == capacity - 1)
        {
            capacity += MEMORY_BLOCK_SIZE;
            text = (char *)realloc(text, capacity);
        }
        last_char = getchar();
    }

    size_t maxGroups = 8;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    int result = regcomp(&regexCompiled, REGEX_STRING, REG_EXTENDED);
    if (result)
    {
        free(text);
        regfree(&regexCompiled);
        return 0;
    };
    char *line;
    line = strtok(text, "\n");
    while (line != NULL)
    {
        result = regexec(&regexCompiled, line, maxGroups, groupArray, 0);

        if (!result)
        {
            for (int j = groupArray[3].rm_so; j < groupArray[3].rm_eo; j++)
            {
                printf("%c", line[j]);
            }
            printf(" - ");
            for (int k = groupArray[7].rm_so; k < groupArray[7].rm_eo; k++)
            {
                printf("%c", line[k]);
            }
            printf("\n");
        }
        line = strtok(NULL, "\n");
    }

    free(text);
    regfree(&regexCompiled);

    return 0;
}