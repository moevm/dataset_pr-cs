#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024
#define EOT "Fin.\n"
#define PATTERN "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?~ ?# (.*)"

typedef struct Text{
    char ** text;
    int size;
} Text;

Text getText();

int main() {
    regex_t regex;
    size_t maxGroups = 3;
    regmatch_t groupArray[maxGroups];

    int err = regcomp(&regex, PATTERN, REG_EXTENDED);

    if (err != 0) {
        printf("Error!");
        return 0;
    }

    Text txt = getText();
    
    for (int i = 0; i < txt.size; i++) {
        err = regexec(&regex, txt.text[i], maxGroups, groupArray, 0);
        if (err == 0) {
            for (int j = groupArray[1].rm_so; j < groupArray[1].rm_eo; j++) {
                printf("%c", txt.text[i][j]);
            }
            printf(" - ");
            for (int k = groupArray[2].rm_so; k < groupArray[2].rm_eo; k++) {
                printf("%c", txt.text[i][k]);
            }
        }
        free(txt.text[i]);
    }
    free(txt.text);
    regfree(&regex);
    return 0;
}

Text getText() {
    Text result;
    char ** text = (char **)malloc(BUF_SIZE * sizeof(char *));
    if (text == NULL) {
        exit(1);
    }

    int size = 0;
    int currBuf = BUF_SIZE;

    char * currSentence = (char *)malloc(BUF_SIZE * sizeof(char));
    if (currSentence == NULL) {
        exit(1);
    }
    while (fgets(currSentence, BUF_SIZE, stdin) && strcmp(currSentence, EOT)) {
        text[size++] = strdup(currSentence);
        if (text[size - 1] == NULL) {
            exit(1);
        }
        if (size == BUF_SIZE - 1) {
            currBuf += BUF_SIZE;
            text = realloc(text, currBuf * sizeof(char *));
            if (text == NULL) {
                exit(1);
            }
        }
        free(currSentence);
        currSentence = (char *)malloc(BUF_SIZE * sizeof(char));
        if (currSentence == NULL) {
            exit(1);
        }
    }
    free(currSentence);

    result.text = text;
    result.size = size - 1;
    return result;
}

