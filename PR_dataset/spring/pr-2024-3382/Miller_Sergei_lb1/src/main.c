#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>




int main ()
{
    char * regexString = "(www.)?((\\w+\\.)+\\w+)(.*)(\\/(\\w+\\.\\w+))";
    size_t maxGroups = 7;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("ERROR\n");
        return 0;
    };

    char s[10000];
    while (fgets(s, 1000, stdin)){
        if (strstr(s, "Fin.") != NULL){
            break;
        }
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0)
        {
                for(int j=groupArray[2].rm_so; j<groupArray[2].rm_eo;j++)
                    printf("%c",s[j]);
                printf(" - ");
           
                for(int j=groupArray[6].rm_so;j<groupArray[6].rm_eo;j++)
                    printf("%c",s[j]);
                printf("\n");
        } 
        

    }
    regfree(&regexCompiled);

    
    
    
    
    
    
    
    return 0;
}

