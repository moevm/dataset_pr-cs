#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *getSentence() {
    char c;
    int len = 0;
    char *sentence = calloc(len, 1);
    while ((c = getchar()) != '\n') {
        sentence = realloc(sentence, len+1);
        sentence[len++] = c;
        if(strcmp(sentence, "Fin.") == 0) return sentence;
    }
    return sentence;
}

int main() {
    regex_t regex;
    const char *pattern = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.+)";
    regcomp(&regex, pattern, REG_EXTENDED);
    char *sentence;
    while (strcmp((sentence = getSentence()), "Fin.") != 0) {
        regmatch_t matches[3];
        if (regexec(&regex, sentence, 3, matches, 0) == 0) {
            printf("%.*s - %.*s\n", matches[1].rm_eo - matches[1].rm_so, &(sentence[matches[1].rm_so]),
                   matches[2].rm_eo - matches[2].rm_so, &(sentence[matches[2].rm_so]));
        }
    }
    return 0;
}