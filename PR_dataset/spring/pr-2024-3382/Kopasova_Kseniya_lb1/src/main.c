#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

#define MAX_LEN 1000

int main() {
	char* regexString = "(www.)?((\\w+\\.)+\\w+)(.*)(\\/(\\w+\\.\\w+))";
    size_t maxGroups = 7;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        return 0;
    }
    
    char text[MAX_LEN];
    while (fgets(text, MAX_LEN, stdin)){
        if (strstr(text, "Fin.") != NULL){
            break;
        }
        if (regexec(&regexCompiled, text, maxGroups, groupArray, 0) == 0){
            char site[MAX_LEN];
            char file[MAX_LEN];
            strncpy(site, text + groupArray[2].rm_so, groupArray[2].rm_eo - groupArray[2].rm_so);
            site[groupArray[2].rm_eo - groupArray[2].rm_so] = '\0';
            
            strncpy(file, text + groupArray[6].rm_so, groupArray[6].rm_eo - groupArray[6].rm_so);
            file[groupArray[6].rm_eo  - groupArray[6].rm_so] = '\0';
            printf("\n%s - %s", site, file);
        }
    }
    regfree(&regexCompiled);
	return 0;
}