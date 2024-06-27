#include <stdio.h>
#include <regex.h>
#include <string.h>


int main ()
{
    char * regexString = "([0-9a-zA-Z_-]+)@[0-9a-zA-Z_-]+: *~ *# (.+)";
    
    size_t maxGroups = 3;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    regcomp(&regexCompiled, regexString, REG_EXTENDED);

    char s[1000];
    while (fgets(s,1000,stdin)){
        if(strstr(s, "Fin.") != NULL){
            break;
        }
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0)
        {
            for (int i = 1; i < maxGroups; i++)
            {
                for(int j=groupArray[i].rm_so;j<groupArray[i].rm_eo;j++)
                    printf("%c",s[j]);
                if (i == 1){
                    printf(" - ");
                }
            }
        }
    }
    regfree(&regexCompiled);
    return 0;
}
