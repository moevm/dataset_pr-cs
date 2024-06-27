#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


int main()
{
    char *regex_str = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.+)";

    regex_t regexCompiled;
    size_t max_groups = 3;
    regmatch_t groupArray[max_groups];

    regcomp(&regexCompiled, regex_str, REG_EXTENDED);

    char *str = malloc(sizeof(char)*1001);

    while(strstr(str, "Fin.") == NULL)
    {
        fgets(str, 1000, stdin);

        if(regexec(&regexCompiled, str, max_groups, groupArray, 0) == 0)
        {
            char* res_user = malloc(sizeof(char)*1001);
            
            strncpy(res_user, str + groupArray[1].rm_so, groupArray[1].rm_eo - groupArray[1].rm_so);
            res_user[groupArray[1].rm_eo - groupArray[1].rm_so] = '\0';

            printf("%s - ", res_user);
            
            char* res_command = malloc(sizeof(char)*1001);

            strncpy(res_command, str + groupArray[2].rm_so, groupArray[2].rm_eo - groupArray[2].rm_so);
            res_command[groupArray[2].rm_eo - groupArray[2].rm_so] = '\0';

            printf("%s", res_command);
            
            free(res_user);
            free(res_command);        
        }

    }

    free(str);
    regfree(&regexCompiled);
    return 0;
}
