#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE  512
#define GROUPS_COUNT 7 
#define GROUP_SITE   3
#define GROUP_FILE   6

char* get_substring(char* input, int start, int end) {
        char* res = malloc(end-start+1);
        memcpy(res, input+start, end-start);
        res[end-start] = '\0';
        return res;
}

int main() {
        const char* regex_pattern = "(\\w+\\:\\/\\/)?(www\\.)?(\\w+(\\.\\w+)+)(\\/\\w+)*\\/(\\w+\\.\\w+)\n";
        regex_t regex;
        if(regcomp(&regex, regex_pattern, REG_EXTENDED)) {
                puts("[ERROR] Unable to compile regex.");
                return 1;
        }

        regmatch_t regexMatch[GROUPS_COUNT];
        char buffer[BUFFER_SIZE];
        fgets(buffer, BUFFER_SIZE, stdin);
        while(!strstr(buffer, "Fin.")) {
                if(regexec(&regex, buffer, GROUPS_COUNT, regexMatch, 0) == 0) {
                        char* sitename = get_substring(buffer, regexMatch[GROUP_SITE].rm_so,
                                                       regexMatch[GROUP_SITE].rm_eo);
                        char* filename = get_substring(buffer, regexMatch[GROUP_FILE].rm_so,
                                                       regexMatch[GROUP_FILE].rm_eo);
                        printf("%s - %s\n", sitename, filename);
                        free(sitename);
                        free(filename);
                }
                fgets(buffer, BUFFER_SIZE, stdin);
        }
        regfree(&regex);
        return 0;
}
