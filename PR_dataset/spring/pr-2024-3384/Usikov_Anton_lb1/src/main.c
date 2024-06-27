#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define STEP 15

int main() {
    int st = STEP;
    char *str = malloc(st);

    for (int i = 0; (str[i] = getchar()); i++) {
        if (i == (st - 2)) {
            st += STEP;
            str = realloc(str, st);
        }
        if (str[i] == '.') {
            str[i + 1] = '\0';
            if (strstr(str, "Fin."))
                break;
        }
    }

char *pattern = "(\\w+)@[a-zA-Z0-9_-]+: ?~ ?# ([^\n]+)";
regex_t regex;
regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);

regmatch_t pmatch[3];
size_t nmatch = 3;
char *start = str;

while (regexec(&regex, start, nmatch, pmatch, 0) == 0) {
    if (pmatch[0].rm_so == -1)
        break;

    char *username_start = start + pmatch[1].rm_so;
    char *username_end = start + pmatch[1].rm_eo;
    char *command_start = start + pmatch[2].rm_so;
    char *command_end = start + pmatch[2].rm_eo;

    printf("%.*s - %.*s\n", (int)(username_end - username_start), username_start,
                            (int)(command_end - command_start), command_start);

    start += pmatch[0].rm_eo;
}
    regfree(&regex);
    free(str);
    return 0;
}
