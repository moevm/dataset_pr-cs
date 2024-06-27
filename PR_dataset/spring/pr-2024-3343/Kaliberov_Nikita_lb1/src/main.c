#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_LINE_LENGTH 1024
#define MAX_GROUPS 10

void extractMatch(char *source, regmatch_t match) {
    for (int i = match.rm_so; i < match.rm_eo; i++) {
        printf("%c", source[i]);
    }
}

int main() {
    char *pattern = "([A-Za-z]+://)?(www\\.)?([A-Za-z0-9.-]+\\.[A-Za-z]+)((/[A-Za-z0-9_-]+)*)/([A-Za-z0-9_-]+\\.[A-Za-z0-9]+)\n";
    regex_t regexCompiled;
    regmatch_t groupArray[MAX_GROUPS];

    if (regcomp(&regexCompiled, pattern, REG_EXTENDED)) {
        fprintf(stderr, "Could not compile regex\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), stdin)) {
        if (strncmp(line, "Fin.", 4) == 0) {
            break;
        }
        if (regexec(&regexCompiled, line, MAX_GROUPS, groupArray, 0) == 0) {
            extractMatch(line, groupArray[3]);
            printf(" - ");
            extractMatch(line, groupArray[6]);
            printf("\n");
        }
    }

    regfree(&regexCompiled);
    return 0;
}