#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define MAX_TEXT 1000
#define MAX_LENGTH 100

char **read_text() {
    char **text = (char **)malloc(MAX_TEXT * sizeof(char *));
    if (!text) {
        fprintf(stderr, "ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_LENGTH];
    int count = 0;

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        text[count] = (char *)malloc(strlen(buffer) + 1);
        if (!text[count]) {
            fprintf(stderr, "ошибка выделения памяти в предложении [%d]\n", count);
            exit(EXIT_FAILURE);
        }
        strcpy(text[count], buffer);
        if (strcmp(buffer, "Fin.") == 0) {
            break;
        }
        count++;
    }

    text = (char **)realloc(text, (count + 1) * sizeof(char *));
    if (!text) {
        fprintf(stderr, "ошибка выделения памяти\n");
        exit(EXIT_FAILURE);
    }
    text[count] = NULL;
    return text;
}

void print_link(regex_t *ptrn, char *sentence) {
    int N;
    regmatch_t match_str[7];
    N = regexec(ptrn, sentence, 7, match_str, 0);
    regmatch_t link = match_str[3];
    regmatch_t file = match_str[6];
    if (!N) {
        for (int i = link.rm_so; i < link.rm_eo; i++) {
            printf("%c", sentence[i]);
        }
        printf(" - ");
        for (int i = file.rm_so; i < file.rm_eo; i++) {
            printf("%c", sentence[i]);
        }
        printf("\n");
    }
}

int main() {
    char **text;
    text = read_text();
    char *pattern = "([a-z]+://)?(www\\.)?([a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)+)/([a-zA-Z0-9]+/)*([a-zA-Z0-9]+\\.[a-zA-Z0-9]+)";
    regex_t ptrn;
    if (regcomp(&ptrn, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "ошибка компиляции регуляторного выражения\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; text[i] != NULL; i++) {
        print_link(&ptrn, text[i]);
        free(text[i]);
    }
    regfree(&ptrn);
    free(text);
    return 0;
}
