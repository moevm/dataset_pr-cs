#include <stdio.h>
#include <regex.h>
#include <string.h>


int main (){   
    char *reRegex = "((http|https|ftp):\\/\\/)?(www\\.)?(([a-zа-я0-9-]+\\.)+[a-zа-я0-9]+)(\\/[a-zа-я0-9-]+)*(\\/([a-zа-я0-9-]+\\.[a-zа-я0-9]+))";
    size_t maxGroups = 9;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

     if (regcomp(&regexCompiled, reRegex, REG_EXTENDED))
    {
        printf("Can't do this regular expression\n");
        return 0;
    }

    char smtext[1000] = "";
    while (strcmp(smtext, "Fin."))
    {
        fgets(smtext, 1000, stdin);
        if (regexec(&regexCompiled, smtext, maxGroups, groupArray, 0) == 0)
        {
            for (int j = groupArray[4].rm_so; j < groupArray[4].rm_eo; j++)
                printf("%c", smtext[j]);
            printf(" - ");
            for (int j = groupArray[8].rm_so; j < groupArray[8].rm_eo; j++)
                printf("%c", smtext[j]);
            printf("\n");
        }
        if (strstr(smtext, "Fin."))
            break;
    }
      
    
    regfree(&regexCompiled);
    return 0;
}