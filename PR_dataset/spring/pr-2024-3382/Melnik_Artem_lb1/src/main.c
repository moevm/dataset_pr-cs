#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


int main()
{
    char *regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# ([a-zA-Z0-9 -_:]+)";
    size_t maxGroups = 3;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    regcomp(&regexCompiled, regexString, REG_EXTENDED);
    
    char *sent=malloc(sizeof(char)*1000);
    while(fgets(sent, 1000, stdin))
    {
        if(strstr(sent, "Fin.")!=NULL)
            break;
            
        if(regexec(&regexCompiled, sent, maxGroups, groupArray, 0)==0)
        {
            char usr[1000];
            strncpy(usr, sent + groupArray[1].rm_so, groupArray[1].rm_eo - groupArray[1].rm_so);
            usr[groupArray[1].rm_eo - groupArray[1].rm_so] = '\0';
            
            char cmd[1000];
            strncpy(cmd, sent + groupArray[2].rm_so, groupArray[2].rm_eo - groupArray[2].rm_so);
            cmd[groupArray[2].rm_eo - groupArray[2].rm_so] = '\0';
            
            printf("%s - %s\n", usr, cmd);
        }

    }
    free(sent);
    regfree(&regexCompiled);
    return 0;
}
