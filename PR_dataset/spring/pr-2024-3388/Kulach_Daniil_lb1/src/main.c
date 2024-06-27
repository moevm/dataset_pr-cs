#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define INCREMENT 20
#define REGEX_PATTERN "(\\w+)@[a-zA-Z0-9_-]+: ?~ ?# (.*)"
#define GROUP_NUM 3

void release_memory(char **sentences, int count) {
    for (int i = 0; i <= count; i++) {
        free(sentences[i]);
    }
    free(sentences);
}

void check_memory_allocation(char **sentences, int count, void *ptr) {
    if (ptr == NULL) {
        release_memory(sentences, count);
        fprintf(stderr, "Error: Memory Allocation Failed\n");
        exit(1);
    }
}

char **read_sentences(int *count) {
    int i = 0, done = 1;
    char ch;
    char **sentences = (char **)malloc(sizeof(char *));
    check_memory_allocation(sentences, 0, sentences);
    sentences[0] = (char *)malloc(INCREMENT * sizeof(char));
    check_memory_allocation(sentences, 0, sentences[i]);
    while (done) {
        int j = 0, size = INCREMENT;
        while (1) {
            if (j % INCREMENT == INCREMENT - 1) {
                size += INCREMENT;
                sentences[i] = (char *)realloc(sentences[i], size * sizeof(char));
                check_memory_allocation(sentences, i, sentences[i]);
            }
            ch = getchar();
            if (ch == '\n') {
                sentences[i][j + 1] = '\0';
                break;
            }
            sentences[i][j] = ch;
            j++;
            sentences[i][j] = '\0';
            if ((strcmp(sentences[i], "Fin.\0") == 0) || ch == EOF) {
                done = 0;
                break;
            }
        }
        if (!done) {
            break;
        }
        i++;
        sentences = (char **)realloc(sentences, (i + 1) * sizeof(char *));
        check_memory_allocation(sentences, i - 1, sentences);
        sentences[i] = (char *)malloc(INCREMENT * sizeof(char));
        check_memory_allocation(sentences, i - 1, sentences[i]);
    }
    *count = i;
    return sentences;
}

int process_sentences_with_regex(char **sentences, int count) {
    regex_t regex;
    int ret;
    regmatch_t matches[3];
    ret = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Error: Regex Compilation Failed\n");
        release_memory(sentences, count);
        regfree(&regex);
        return 1;
    }
    for (int i = 0; i <= count; i++) {
        ret = regexec(&regex, sentences[i], GROUP_NUM, matches, 0);
        if (ret == 0) {
            for (int p = matches[1].rm_so; p < matches[1].rm_eo; p++) {
                printf("%c", sentences[i][p]);
            }
            printf(" - ");
            for (int p = matches[2].rm_so; p < matches[2].rm_eo; p++) {
                printf("%c", sentences[i][p]);
            }
            printf("\n");
        } else if (ret && ret != REG_NOMATCH) {
            fprintf(stderr, "Error: Regex Matching Failed\n");
            release_memory(sentences, count);
            regfree(&regex);
            return 1;
        }
    }
    release_memory(sentences, count);
    regfree(&regex);
    return 0;
}

int main() {
    char **sentences;
    int count = 0, status = 0;
    sentences = read_sentences(&count);
    status = process_sentences_with_regex(sentences, count);
    return status;
}
