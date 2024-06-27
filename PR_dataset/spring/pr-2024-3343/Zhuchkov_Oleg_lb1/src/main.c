#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    char * ex = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.+)";
    regex_t regex;
    regmatch_t match[3];
    regcomp(&regex, ex, REG_EXTENDED);
    char line[201];
    do {
        fgets(line, 200, stdin);
        if (regexec(&regex, line, 3, match, 0) == 0) {
            printf("%.*s - %.*s", match[1].rm_eo-match[1].rm_so,
                   line+match[1].rm_so, match[2].rm_eo-match[2].rm_so,
                   line+match[2].rm_so);
        }
    } while (strcmp(line, "Fin.") != 0);
    return 0;
}