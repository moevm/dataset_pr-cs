#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
int main()
{
    regex_t regex;
    regmatch_t groups[4];
    char* pattern = "([A-Za-z0-9_]+)@([A-Za-z0-9_-]+):\\s?~\\s?# (.+)";
    regcomp(&regex, pattern, REG_EXTENDED);
    char sentence[100];
    char breakWord[10] = "Fin.";
    while (strcmp(sentence,breakWord))
    {
        fgets(sentence,100,stdin);
        if(regexec(&regex,sentence,4,groups,0)==0)
        {

            for (int i = groups[1].rm_so; i < groups[1].rm_eo; ++i)
            {
                printf("%c",sentence[i]);
            }
            printf(" - ");
            for (int i = groups[3].rm_so; i < groups[3].rm_eo; ++i)
            {
                printf("%c",sentence[i]);
            }


        }
    }
    return 0;

}


