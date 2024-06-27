#include <stdio.h>
#include <regex.h>
#include <string.h>

int main() {
    char s[101];
    size_t groups = 3;
    regex_t regex;
    regmatch_t matches[groups];

    char* pattern = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.*)";
    if (regcomp(&regex, pattern, REG_EXTENDED)) {
        return 1;
    }

    while (fgets(s, 100, stdin)) {
        if (strstr(s, "Fin.\n") != NULL) {
            break;
        }

        if (regexec(&regex, s, groups, matches, 0) == 0) {
            
            if (matches[1].rm_so != -1 && matches[2].rm_so != -1) {
                s[matches[1].rm_eo] = '\0'; 
                s[matches[2].rm_eo] = '\0';
                printf("%s - %s", &s[matches[1].rm_so], &s[matches[2].rm_so]);
            }
        }
    }

    regfree(&regex); 

    return 0;
}