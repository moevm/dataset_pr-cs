#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_GROUPS 5


int main() {

    char *regexString = "(\\w+)@([A-Za-z0-9_-]+)(: ?\\~ ?\\# )(.+\n)";

    regex_t regexCompiled;
    regmatch_t groupArray[MAX_GROUPS];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("[Can't compile expression]\n");
        return 0;
    }

    char *text_line = (char *)malloc(sizeof(char) * 1000);
    
    
    while (fgets(text_line, 1000, stdin) != NULL) {

        if (strncmp(text_line, "Fin.\n", 5) == 0) break;

        if (regexec(&regexCompiled, text_line, 5, groupArray, 0) == 0) {
            for (size_t i = groupArray[1].rm_so; i < groupArray[1].rm_eo; i++) {
                printf("%c", text_line[i]);
            }

            printf(" - ");

            for (size_t j = groupArray[4].rm_so; j < groupArray[4].rm_eo; j++) {
                printf("%c", text_line[j]);
            }
        }
            free(text_line);
            text_line = (char *)malloc(sizeof(char) * 1000);
    }

    free(text_line);
    regfree(&regexCompiled);

    return 0;
}
