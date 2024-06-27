#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char *regexString = "([A-Za-z0-9_]+)@[0-9A-Za-z_-]+: ?~ ?# ([ -~]+)\n";
    size_t maxGroups = 3;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if(regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("Wow, no - cant comile regular expression\n");
        return 1;
    }

    char s[100];
    char *target = "Fin.";
    while(!strstr(s, target)){
        fgets(s, 100, stdin);
        if(!regexec(&regexCompiled, s, maxGroups, groupArray, 0)){
            for(size_t i = 1; i < maxGroups; i++){
                if(groupArray[i].rm_so == -1)
                    break;
                for(size_t j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++)
                    printf("%c", s[j]);
                if(i < maxGroups - 1)
                    printf(" - "); 
            }
            printf("\n");
        }
    }
    regfree(&regexCompiled);
    return 0;
}