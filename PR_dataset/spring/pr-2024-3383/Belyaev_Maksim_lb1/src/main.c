#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_SIZE 500

int main() {
    regex_t reg;
    char input[MAX_SIZE] = {'\0'};
    int i = 0;
    char symbol;
    while (1) {
        symbol = getchar();
        input[i] = symbol;
        i++;
        if (strstr(input, "\nFin.")) {
            break;
        }
        
    }
    char *token = strtok(input, "\n");
    char *lines[MAX_SIZE];
    i=0;
    while (token != NULL){
        lines[i]= malloc(strlen(token) + 1);
        strcpy(lines[i], token);
        i++;
        token = strtok(NULL, "\n");
    }
    int numLines=i;
    size_t nmatch = 4;
    regmatch_t match[nmatch];

    char *find = "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+): ?~ ?# (.+)";
    if (!regcomp(&reg, find, REG_EXTENDED)) {
        for (i = 0; i < numLines; i++) {
            if (!regexec(&reg, lines[i], nmatch, match, 0)){
                printf("\n");
                for (int j = match[1].rm_so; j < match[1].rm_eo; j++) {
                    printf("%c", lines[i][j]);
                }
                printf(" - ");
                for (int j = match[3].rm_so; j < match[3].rm_eo; j++) {
                    printf("%c", lines[i][j]);
                }
            }
        }
        regfree(&reg);
    }
    for (i = 0; i < numLines; ++i) {
        free(lines[i]);
    }
    return 0;
}

