#include <stdio.h>
#include <regex.h>
#include <string.h>


int main ()
{
    char *regexString = "((http|https|ftp):\\/\\/)?(www\\.)?(([a-zа-я0-9-]+\\.)+[a-zа-я0-9]+)(\\/[a-zа-я0-9-]+)*(\\/([a-zа-я0-9-]+\\.[a-zа-я0-9]+))";
    size_t maxGroups = 9;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

     if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Can't compile regular expression\n");
        return 0;
    };

    char s[100] = "";
    while (strcmp(s, "Fin."))
    {
        fgets(s, 100, stdin);
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0)
        {
            for (int j = groupArray[4].rm_so; j < groupArray[4].rm_eo; j++)
                printf("%c", s[j]);
            printf(" - ");
            for (int j = groupArray[8].rm_so; j < groupArray[8].rm_eo; j++)
                printf("%c", s[j]);
            printf("\n");
        }
    }
    regfree(&regexCompiled);
    return 0;
}
