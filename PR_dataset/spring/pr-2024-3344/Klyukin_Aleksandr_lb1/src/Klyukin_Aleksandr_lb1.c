#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main() {    
    char *text = NULL;
    char buffer[100];
    size_t text_length = 0;
    while (1) {
        fgets(buffer, 100, stdin);
        if (strstr(buffer, "Fin.") != NULL) {
            break;
        }
        text = realloc(text, text_length + strlen(buffer) + 1);
        strcpy(text + text_length, buffer);
        text_length += strlen(buffer);
    }
    const char *pattern = "[A-Za-z_0-9]+@[A-Za-z0-9_-]+: ?\\~ ?\\# ?.";
    regex_t regex;
    int reti;
    regmatch_t match;
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    reti = regexec(&regex, text, 1, &match, 0);
    while (reti == 0) {
        for (int i = match.rm_so; i < match.rm_eo; i++) {
            if(text[i] == '@'){
                printf("%c", ' ');
                while (text[i] != '#')
                {
                    i = i + 1;
                }
                printf("-");
                i= i + 1;
                while (text[i] != '\n')
                {
                    printf("%c", text[i]);
                    i = i + 1;
                }
            }
            printf("%c", text[i]);
            text[i] = ' ';
        }
        memmove(text + match.rm_so, text + match.rm_eo, strlen(text) - match.rm_eo + 1);
        reti = regexec(&regex, text, 1, &match, 0);
    }
    regfree(&regex);
    free(text);
    return 0;
}
