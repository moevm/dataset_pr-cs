#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


int main() {
    char *pattern = "(\\w+)@([A-Za-z0-9_-]+)(: ?\\~ ?\\# )(.+\n)";
    regex_t regexCompiled;
    regmatch_t groups[4];

    if (regcomp(&regexCompiled, pattern, REG_EXTENDED)) {
        printf("[Can't compile expression]\n");
        return 0;
    }

    char *txtString = (char *)malloc(sizeof(char) * 1000);

    // Reading until "Fin.\n"
    while (fgets(txtString, 1000, stdin) != NULL) {
        if (strncmp(txtString, "Fin.\n", 5) == 0) break;

        // Check for regex match
        if (regexec(&regexCompiled, txtString, 5, groups, 0) == 0) {
            // Print
            for (size_t i = groups[1].rm_so; i < groups[1].rm_eo; i++) {
                printf("%c", txtString[i]);
            }
            printf(" - ");
            // Print
            for (size_t j = groups[4].rm_so; j < groups[4].rm_eo; j++) {
                printf("%c", txtString[j]);
            }
        }
    }

    // Free allocated memory
    free(txtString);
    regfree(&regexCompiled);
    return 0;
}
