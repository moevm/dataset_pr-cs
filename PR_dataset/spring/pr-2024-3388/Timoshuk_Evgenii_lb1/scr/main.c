#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

void input(char*** text, int* text_sentense) {
    char* sentence = malloc(10 * sizeof(char));
    int sentence_len = 0;
    char character;

    while (1) {
        character = getchar();
        sentence = realloc(sentence, (sentence_len + 1) * sizeof(char));
        sentence[sentence_len++] = character;

        if (character == '\n') {
            sentence[sentence_len - 1] = '\0';
            (*text)[*text_sentense] = malloc(sentence_len * sizeof(char));
            strcpy((*text)[*text_sentense], sentence);
            (*text_sentense)++;
            *text = realloc(*text, ((*text_sentense) + 1) * sizeof(char*));
            sentence_len = 0;
        }
        if (strstr(sentence, "Fin.") != NULL) {
            break;
        }
    }
    free(sentence);
}


void processInput(char** text, int len_text) {
    int m = 0;
    char* regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?~ ?# ([a-zA-Z0-9 -_:]+)";
    size_t maxGroups = 3;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("Wow, no - can't compile regular expression\n");
        return;
    }

    while (m < len_text) {
        if (strstr(text[m], "Fin.") == NULL) {
            if (regexec(&regexCompiled, text[m], maxGroups, groupArray, 0) == 0) {
                for (int i = 1; i < maxGroups; i++) {
                    if (groupArray[i].rm_so == -1)
                        break;
                    for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++)
                        printf("%c", text[m][j]);
                    if (i == 1) {
                        printf(" - ");
                    }
                }
                printf("\n");
            }
        }
        m++;
    }

    regfree(&regexCompiled);
    for (int i = 0; i < len_text; i++) {
        free(text[i]);
    }
    free(text);
}

int main() {
    int len_text = 0;
    char** text = malloc((len_text + 1) * sizeof(char*));
    input(&text, &len_text);
    processInput(text, len_text);

    return 0;
}