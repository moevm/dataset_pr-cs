#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REGEX "([A-Za-z]+:\\/\\/)?(www\\.)?([a-zA-Z\\.\\-\\_]+)\\/([A-Za-z\\-\\_]+\\/)*([A-Za-z0-9\\-\\_]+\\.[A-Za-z0-9\\-]+)$"

void printResFormatted(regmatch_t match[8], char *url, int isNewLine) {
    if (match[3].rm_so != -1 && match[5].rm_so != -1) {
        char group2[match[3].rm_eo - match[3].rm_so + 1];
        char group6[match[5].rm_eo - match[5].rm_so + 1];
        strncpy(group2, url + match[3].rm_so, match[3].rm_eo - match[3].rm_so);
        strncpy(group6, url + match[5].rm_so, match[5].rm_eo - match[5].rm_so);
        group2[match[3].rm_eo - match[3].rm_so] = '\0';
        group6[match[5].rm_eo - match[5].rm_so] = '\0';
        if (!isNewLine && strstr(group2, ".")) {
            printf("%s - %s", group2, group6);
        } else if (strstr(group2, ".")) {
            printf("\n%s - %s", group2, group6);
        }
    } else {
        printf("Не удалось найти соответствия для доменного имени и имени файла\n");
    }
}

int main() {
    char** sentences = malloc(10 * sizeof(char*));
    int len = 0;
    regex_t regex;
    regmatch_t match[8];

    regcomp(&regex, REGEX, REG_EXTENDED);

    while (1) {
        if (len % 10 == 8) {
            sentences = realloc(sentences, (len + 10) * sizeof(char*));
        }

        sentences[len] = malloc(1000);
        scanf("%s", sentences[len]);

        if (strcmp(sentences[len], "Fin.") == 0) {
            break;
        }

        len++;
    }

    int isfirst = 0;
    char* currentSentence = malloc(1000);

    for (int i = 0; i < len; i++) {
        if (regexec(&regex, sentences[i], 8, match, 0) == 0) {
            strcpy(currentSentence, sentences[i] + match->rm_so);
            if (strstr(currentSentence, "..") || !strstr(currentSentence, ".") || (currentSentence[0] == '.' || (currentSentence[strlen((currentSentence))-1] == '.'))) {
                continue;
            } else {
                printResFormatted(match, sentences[i], isfirst++);
            }
        }
    }

    for (int i = 0; i < len; i++) {
        free(sentences[i]);
    }
    free(sentences);

    return 0;
}