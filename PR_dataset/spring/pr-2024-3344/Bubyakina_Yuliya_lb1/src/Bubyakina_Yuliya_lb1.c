#include <stdio.h>
#include <regex.h>
#include <string.h>

int main()
{
    char *regexPattern = "(\\w+)@[0-9a-zA-Z_-]+: ?~ ?# (.+\n)";
    regmatch_t matchGroups[3];
    regex_t compiledRegex;
    regcomp(&compiledRegex, regexPattern, REG_EXTENDED);
    char input[100] = "";
    while (strcmp(input, "Fin."))
    {
        fgets(input, 100, stdin);
        if (regexec(&compiledRegex, input, 3, matchGroups, 0) == 0)
        {
                for (size_t j = matchGroups[1].rm_so; j < matchGroups[1].rm_eo; j++)
                {
                    printf("%c", input[j]);
                }
                printf(" - ");
                for (size_t j = matchGroups[2].rm_so; j < matchGroups[2].rm_eo; j++)
                {
                    printf("%c", input[j]);
                }
        }
    }
    regfree(&compiledRegex);
    return 0;
}
