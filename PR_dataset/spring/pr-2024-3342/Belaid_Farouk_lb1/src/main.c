#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_SENTENCE_LENGTH 1000
#define MAX_MATCHES 9

void printMatchedSubstring(char *sourceString, regmatch_t matchedRegion) {
    for (int i = matchedRegion.rm_so; i < matchedRegion.rm_eo; i++) {
        printf("%c", sourceString[i]);
    }
}

int findMatch(char *text, char *pattern, regex_t *compiledRegex, regmatch_t matches[], size_t maxMatches) {
    int result = regcomp(compiledRegex, pattern, REG_EXTENDED);
    if (result != 0) {
        return result;
    }
    result = regexec(compiledRegex, text, maxMatches, matches, 0);
    return result;
}

int main() {
    regex_t compiledRegex;
    regmatch_t matchRegions[MAX_MATCHES];
    int returnValue;
    int sentenceCount = 0;
    char **inputText = NULL;
    char sentence[MAX_SENTENCE_LENGTH];
    char *pattern = "([a-zA-Z]+://)?(www\\.)?([a-zA-Z0-9-]+(\\.[a-zA-Z0-9]+)+)/((\\w+/)*)([a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+))*\n$";

    while (fgets(sentence, MAX_SENTENCE_LENGTH, stdin)) {
        if (strcmp(sentence, "Fin.\n") == 0) {
            break;
        }
        sentenceCount++;
        char **tempInputText = realloc(inputText, sizeof(char *) * sentenceCount);
        if (tempInputText == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        inputText = tempInputText;
        inputText[sentenceCount - 1] = strdup(sentence);
        if (inputText[sentenceCount - 1] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            for (int i = 0; i < sentenceCount - 1; i++) {
                free(inputText[i]);
            }
            free(inputText);
            return 1;
        }
    }

    for (int i = 0; i < sentenceCount; i++) {
        returnValue = findMatch(inputText[i], pattern, &compiledRegex, matchRegions, MAX_MATCHES);
        if (returnValue == 0) {
            printMatchedSubstring(inputText[i], matchRegions[3]);
            printf(" - ");
            printMatchedSubstring(inputText[i], matchRegions[7]);
            if (i != sentenceCount - 1) {
                printf("\n");
            }
        }
    }
    regfree(&compiledRegex);

    for (int i = 0; i < sentenceCount; i++) {
        free(inputText[i]);
    }
    free(inputText);

    return 0;
}