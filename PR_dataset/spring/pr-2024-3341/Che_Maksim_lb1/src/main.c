#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char const *argv[])
{
    char *text = (char *)malloc(sizeof(char));
    char **sentences = (char **)malloc(sizeof(char *));

    int count = 0;
    char symbol;
    while (strstr(text, "Fin.") == NULL)
    {
        symbol = getchar();
        text[count++] = symbol;
        text = realloc(text, sizeof(char) * (count + 2));
    }
    text[count] = '\0';
    char *sentence = strtok(text, "\n");
    count = 0;
    while (sentence != NULL)
    {
        sentences[count++] = sentence;
        sentences = (char **)realloc(sentences, sizeof(char *) * (count + 1));
        sentence = strtok(NULL, "\n");
    }
    char *reg_sentence = "([a-zA-Z]+:\\/{2})?(w{3}\\.)?([a-zA-Z0-9\\-]+(\\.[a-zA-Z\\-]+)+)(\\/[A-z]+)*(\\/[A-z0-9]+\\.[A-z0-9]+)";
    size_t maxGroups = 7;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    if (regcomp(&regexCompiled, reg_sentence, REG_EXTENDED))
    {
        printf("Wowm no - can't compile regular expression\n");
        return 0;
    };
    for (int i = 0; i < count; i++)
    {
        if (regexec(&regexCompiled, sentences[i], maxGroups, groupArray, 0) == 0)
        {
            for (int j = groupArray[3].rm_so; j < groupArray[3].rm_eo; j++)
                printf("%c", sentences[i][j]);
            printf(" - ");
            for (int j = groupArray[6].rm_so + 1; j < groupArray[6].rm_eo; j++)
                printf("%c", sentences[i][j]);
            printf("\n");
        }
    }
    free(text);
    free(sentences);
    regfree(&regexCompiled);
    return 0;
}

