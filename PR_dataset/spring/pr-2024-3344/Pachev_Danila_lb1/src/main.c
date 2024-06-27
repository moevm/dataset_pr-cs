#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(void) {
    char *text = malloc(sizeof(char) * 1);
    char ch;
    int len = 0;
    while (1) {
        ch = getchar();
        text = realloc(text, sizeof(char) * len + 2);
        text[len++] = ch;
        text[len] = '\0';
        if (strstr(text, "Fin.")) {
            break;
        }
    }
    char **sentences_array = malloc(sizeof(char *));
    int len_sentences_array = 0;
    char *token = strtok(text, "\n");
    while (token) {
        sentences_array[len_sentences_array++] = strdup(token);
        sentences_array = realloc(sentences_array, sizeof(char *) * (len_sentences_array + 1));
        token = strtok(NULL, "\n");
    }
    regex_t regex;
    if (regcomp(&regex, "([A-Za-z0-9_]+)@([A-Za-z0-9_-]+)(: ?)(~ ?)(\\#) ?(.+)", REG_EXTENDED)) {
        printf("can't compile regular expression\n");
        return 0;
    };
    int max_groups = 7;
    for (int i = 0; i < len_sentences_array; i++) {
        regmatch_t group_array[max_groups];
        int value;
        value = regexec(&regex, sentences_array[i], max_groups, group_array, 0);
        if (value == 0) {
            for (int j = group_array[1].rm_so; j < group_array[1].rm_eo; j++) {
                printf("%c", sentences_array[i][j]);
            }
            printf(" - ");
            for (int j = group_array[6].rm_so; j < group_array[6].rm_eo; j++) {
                printf("%c", sentences_array[i][j]);
            }
            printf("\n");
        }

    }

    free(text);
    for (int i = 0; i < len_sentences_array; i++) {
        free(sentences_array[i]);
    }
    free(sentences_array);
    regfree(&regex);
    return 0;

}
