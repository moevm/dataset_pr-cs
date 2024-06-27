#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define LEN_STRING 1000

int main()
{
    char *regexString = "([A-Za-z]+:\\/\\/)?(www\\.)?(([A-Za-z0-9\\-]+\\.)+[A-Za-z0-9\\-]+)\\/([A-Za-z0-9\\/\\-_]+\\/)*([A-Za-z0-9_\\-]+\\.[A-Za-z0-9]+)";
    char str[LEN_STRING];
    regex_t regexCompiled;
    regmatch_t groupArray[7];
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Error in regexString\n");
        return 0;
    }
    while (101)
    {
        fgets(str, LEN_STRING, stdin);
        if (strstr(str, "Fin.") != 0)
        {
            break;
        }
        else if (regexec(&regexCompiled, str, 7, groupArray, 0) == 0)
        {
            for (int i = groupArray[3].rm_so; i < groupArray[3].rm_eo; i++)
            {
                printf("%c", str[i]);
            }
            printf(" - ");
            for (int i = groupArray[6].rm_so; i < groupArray[6].rm_eo; i++)
            {
                printf("%c", str[i]);
            }
            printf("\n");
        }
    }
    regfree(&regexCompiled);
    return 0;
}