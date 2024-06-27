#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define groupSize 3

char *getSentence() {
    char ch;
    int len = 0;
    char *sentence = calloc(len+1, sizeof(char));
    while ((ch = getchar()) != '\n') {
        sentence = realloc(sentence, sizeof(char) * len+2);
        sentence[len++] = ch;
        if(strcmp(sentence, "Fin.") == 0) return sentence;
    }
    return sentence;
}

int main() {
    regex_t regex;
    const char *expression = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.+)";
    regcomp(&regex, expression, REG_EXTENDED);
    char *sentence;
    while (strcmp((sentence = getSentence()), "Fin.") != 0) {
        regmatch_t matches[groupSize];
        if (regexec(&regex, sentence, groupSize, matches, 0) == 0) {
            printf("%.*s - %.*s\n", matches[1].rm_eo - matches[1].rm_so, &(sentence[matches[1].rm_so]),
                   matches[2].rm_eo - matches[2].rm_so, &(sentence[matches[2].rm_so]));
        }
        free(sentence);
    }
    return 0;
}