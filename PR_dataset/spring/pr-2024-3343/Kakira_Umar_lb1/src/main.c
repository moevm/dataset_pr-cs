#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define GROUP_SIZE 3

char *fetchSentence() {
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
    const char *pattern = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.+)";
    regcomp(&regex, pattern, REG_EXTENDED);
    char *sentence;
    while (strcmp((sentence = fetchSentence()), "Fin.") != 0) {
        regmatch_t matches[GROUP_SIZE];
        if (regexec(&regex, sentence, GROUP_SIZE, matches, 0) == 0) {
            printf("%.*s - %.*s\n", matches[1].rm_eo - matches[1].rm_so, &(sentence[matches[1].rm_so]),
                   matches[2].rm_eo - matches[2].rm_so, &(sentence[matches[2].rm_so]));
        }
        free(sentence);
    }
    return 0; 
}