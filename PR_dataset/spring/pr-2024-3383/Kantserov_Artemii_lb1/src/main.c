#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#define step 100
#define pattern "([a-z0-9]+\\:\\/\\/)?(www.)?(([a-z0-9]+\\.)+[a-z0-9]+)(\\/[a-z0-9]+)*\\/([a-z0-9]+\\.[a-z0-9]+)"
char* input() {
    int size_text = step;
    char* text = malloc(sizeof(char) * size_text);;
    int index = 0;
    char symbol;
    while (1) {
        while ((symbol = getchar()) != '.') {
            if (index+2>size_text) {
                size_text += step;
                text = realloc(text, sizeof(char) * size_text);
            }
            text[index++] = symbol;
        }
        text[index++] = '.';
        if (strstr(text, "Fin.") != NULL) {break;}
    }
    text[index] = '\0';
    return text;
}
int main () {
    regex_t regex;
    regmatch_t domens[7];
    regcomp(&regex, pattern, REG_EXTENDED);
    char* text = input();
    char* token = strtok(text, "\n");
    while (token != NULL) {
        if (regexec(&regex, token, 7, domens, REG_EXTENDED) == 0) {
            printf("%.*s - ", (int)(domens[3].rm_eo - domens[3].rm_so), token + domens[3].rm_so);
            printf("%.*s\n", (int)(domens[6].rm_eo - domens[6].rm_so), token + domens[6].rm_so);
        }
        token = strtok(NULL, "\n");
    }
    return 0;
}