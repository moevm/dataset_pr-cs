#include <stdio.h>
#include <string.h>
#include <regex.h>

int main()
{
    char *regexString = "([A-Za-z0-9_]+)@[A-Za-z0-9_-]+: *~ *# ([ -~]+)\n";
    size_t maxGroups = 3;

    regex_t regexCompiled;
    regmatch_t groupsArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Error, string hasn't compiled\n");
        return 0;
    }

    int tab_flag = 0;
    int i;
    char s[102];
    fgets(s, 101, stdin);
    while (strcmp(s, "Fin."))
    {
        if (regexec(&regexCompiled, s, maxGroups, groupsArray, 0) == 0)
        {
            if (tab_flag)
            {
                printf("\n");
            }
            else
            {
                tab_flag = 1;
            }

            i = 1;
            for (int j = groupsArray[i].rm_so; j < groupsArray[i].rm_eo; j++)
            {
                printf("%c", s[j]);
            }

            printf(" - ");

            i++;
            for (int j = groupsArray[i].rm_so; j < groupsArray[i].rm_eo; j++)
            {
                printf("%c", s[j]);
            }
        }
        fgets(s, 101, stdin);
    }
    regfree(&regexCompiled);
}