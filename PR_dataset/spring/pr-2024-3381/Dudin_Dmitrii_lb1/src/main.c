#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define CAP 1024
#define MAX_G 5
#define TERMINAL "Fin."

int main() {
    char* sentence = (char*)calloc(CAP, sizeof(char));

    regex_t regexCompiled;
    regmatch_t groupArray[MAX_G];
    char* regexString = "([A-Za-z0-9_]+)@([A-Za-z0-9_-]+)(: ?~ ?#) (.+)\n";
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        return 0;
    }
    
    while (1) {
        fgets(sentence, CAP, stdin);
        if (strstr(sentence, TERMINAL)) {
            break;
        }

        if (regexec(&regexCompiled, sentence, MAX_G, groupArray, 0) == 0) {
            for (size_t i = groupArray[1].rm_so; i < groupArray[1].rm_eo; i++) {
                printf("%c", sentence[i]);
            }
            printf(" - ");
            for (size_t i = groupArray[4].rm_so; i < groupArray[4].rm_eo; i++) {
                printf("%c", sentence[i]);
            }
            printf("\n");
        }
    }

    free(sentence);
    regfree(&regexCompiled);
    return 0;
}