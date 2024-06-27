#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_START 100

char * scan_sent(){
    int i = 0;
    int len = SIZE_START;
    char c = getchar();
    char * sentence = malloc(sizeof(char)*len);
    for( ;c != '\n' && c!=EOF ;i++){
        if (i >= len) {
            len*=2;
            sentence = realloc(sentence, len * sizeof(char));
        }
        sentence[i] = c;
        c = getchar();
    }
    sentence[i++] = '\0';
    return sentence;
}

int main() {
    regex_t reg;
    char* pattern = "([a-z]+://)?(www\\.)?([a-z]+(\\.[a-z]+)+)\\/(([a-z]+\\/)*)([a-z]+\\.[a-z0-9]+)*$";
    int check;
    regmatch_t pmatch[9];
    while (1) {
        char* str = scan_sent();

        if (strcmp(str, "Fin.") == 0 || str[0] == '\0') {
            free(str);
            break;
        }
        if ((check = regcomp(&reg, pattern, REG_EXTENDED)) != 0) {
            printf("ERROR\n");
        }
        if (regexec(&reg, str, 9, pmatch, 0) == 0) {
            printf("%.*s - %.*s\n", pmatch[3].rm_eo - pmatch[3].rm_so, str + pmatch[3].rm_so,
                pmatch[7].rm_eo - pmatch[7].rm_so, str + pmatch[7].rm_so);
        }
        free(str);
    }
    regfree(&reg);
    return 0;
}