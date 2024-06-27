#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>


int main ()
{
    char * regexString = "(\\w+)@([A-Za-z0-9_-]+)(:\\s?~\\s?#\\s)(.+)";
    size_t maxGroups = 5;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Can't compile regular expression\n");
        return 0;
    };
    
    char *s = (char*)malloc(1000 * sizeof(char));

     while (fgets(s, 1000, stdin) && strcmp(s, "Fin.\n") != 0){
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0)
        {       
            for(int j=groupArray[1].rm_so;j<groupArray[1].rm_eo;j++)
                printf("%c", s[j]);
            printf(" - ");
            for(int j=groupArray[4].rm_so;j<groupArray[4].rm_eo;j++)
                printf("%c", s[j]); 
        }
    }
    
    free(s);
    regfree(&regexCompiled);

    return 0;
}