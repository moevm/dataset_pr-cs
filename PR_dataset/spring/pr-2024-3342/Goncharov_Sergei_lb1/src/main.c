#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#define BREAK_SENTENCE "Fin."

int main() {
    regex_t regex;
    regmatch_t groups[4];                                             //group[1] - username, group[2] - pc name, group[3] - command
    char* regular_expression = "([A-Za-z0-9_]+)@([A-Za-z0-9_-]+):\\s?~\\s?# (.+)";
    regcomp(&regex, regular_expression, REG_EXTENDED);

    char sentence[100];

    while (strcmp(sentence, BREAK_SENTENCE)) {

        fgets(sentence, 100, stdin);

        if (regexec(&regex, sentence, 4, groups, 0) == 0) {           //0 - found match, REG_NOMATCH - no match, nonzero value - error

            for (int i = groups[1].rm_so; i < groups[1].rm_eo; i++) { //rm_so - смещение на начало строки
                printf("%c", sentence[i]);
            }
            printf(" - ");

            for (int i = groups[3].rm_so; i < groups[3].rm_eo; i++) { //rm_eo - смещение на конец подстроки
                printf("%c", sentence[i]);
            }

        }
    }
    regfree(&regex);
    return 0;
}