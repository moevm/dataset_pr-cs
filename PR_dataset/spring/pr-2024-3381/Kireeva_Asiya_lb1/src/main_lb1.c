#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_SIZE 100
#define MAX_GROUPS 7
#define WEBSITE 3
#define FILE 6

int main() {
    char buffer[MAX_SIZE];
    regex_t reg_str;
    int status;
    regmatch_t groups[MAX_GROUPS];

    regcomp(&reg_str, "(\\w+\\:\\/\\/)?(www\\.)?(\\w+(\\.\\w+)+)(\\/\\w+)*\\/(\\w+\\.\\w+)", REG_EXTENDED);
    while (!strstr(buffer, "Fin.")) {
        fgets(buffer, MAX_SIZE, stdin);
        status = regexec(&reg_str, buffer, MAX_GROUPS, groups, 0);
        if (!status) {
            for (int j = groups[WEBSITE].rm_so; j < groups[WEBSITE].rm_eo; j++) {
                printf("%c", buffer[j]);
            }
            printf(" - ");
            for (int j = groups[FILE].rm_so; j < groups[FILE].rm_eo; j++) {
                printf("%c", buffer[j]);
            }
            printf("\n");
        }
    }
    regfree(&reg_str);
    return 0;
}
