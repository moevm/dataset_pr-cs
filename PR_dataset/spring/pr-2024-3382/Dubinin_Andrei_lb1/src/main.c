#include <stdio.h>
#include <string.h>
#include <regex.h>
#include <stdlib.h>

#define MAX_SIZE 1024

int main() {
	char * regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# ([a-zA-Z -_]+)";
	
    size_t maxGroups = 3;
    regmatch_t groupArray[maxGroups];
    regex_t regexCompiled;
    regcomp(&regexCompiled, regexString, REG_EXTENDED);
    
    char sent[MAX_SIZE];
    int len_name, len_cmd;
    
    while (fgets(sent, MAX_SIZE, stdin)) {
        if (regexec(&regexCompiled, sent, maxGroups, groupArray, 0) == 0) {
            
            len_name = groupArray[1].rm_eo - groupArray[1].rm_so;
            len_cmd = groupArray[2].rm_eo - groupArray[2].rm_so;
            
            printf("%.*s - ", len_name, sent + groupArray[1].rm_so);
            printf("%.*s\n", len_cmd, sent + groupArray[2].rm_so);
            
        } else if (strstr(sent, "Fin.") != NULL) {
            break;
        }
    }
    
    regfree(&regexCompiled);
	return 0;
}