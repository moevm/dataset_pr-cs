#include <stdio.h>
#include <string.h>
#include <regex.h>

int main()
{
    char * regexString = "([a-zA-Z_0-9]+)@[a-zA-Z_0-9-]+: ?~ ?# ([ -~]+)\n";
    size_t maxGroups = 3;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Can't compile\n");
        return 0;
    }

    char s[100]; int i;
    while (fgets(s, 100, stdin))
    {
        if (!strcmp(s, "Fin."))
            break;
        if (!regexec(&regexCompiled, s, maxGroups, groupArray, 0))
        {
            i = 1;
            for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++)
                printf("%c", s[j]);

            printf(" - ");
            
            i = 2;
            for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++)
                printf("%c", s[j]);
                
            printf("\n");
        }
    }

    regfree(&regexCompiled);

    return 0;
}