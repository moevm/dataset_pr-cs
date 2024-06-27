#include <stdio.h>
#include <regex.h>
#include <string.h>

void printGroup(regmatch_t *groups, char *buffer, int index)
{
    for (size_t i = groups[index].rm_so; i < groups[index].rm_eo; i++)
    {
        printf("%c", buffer[i]);
    }
}

int main()
{
    char *regexStr = "(\\w+)@([0-9a-zA-Z_-]+): ?~ ?# (.+\n)";

    regex_t regexComp;
    regcomp(&regexComp, regexStr, REG_EXTENDED);

    regmatch_t groups[4];

    char buffer[1000] = "";
    while (strcmp(buffer, "Fin."))
    {
        fgets(buffer, 1000, stdin);
        if (regexec(&regexComp, buffer, 4, groups, 0) == 0)
        {
            printGroup(groups, buffer, 1);
            printf(" - ");
            printGroup(groups, buffer, 3);
        }
    }
    regfree(&regexComp);
    return 0;
}