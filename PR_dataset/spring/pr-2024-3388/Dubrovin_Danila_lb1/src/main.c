#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define SENTENCE_BUFFER 100
#define TEXT_START_BUFFER 10
#define FIN "Fin.\n"
#define REGEX_PATTERN "([a-zA-Z0-9_]{1,})@[a-zA-Z0-9_-]{1,}:\\s{0,}?~\\s{0,}# (.{1,})"
#define MAX_GROUP 3
#define CMP_LEN 4

void read_sentences(char ***text, char *sentence, size_t *buffer_len, size_t *counter) {
    for (*counter = 0; *counter < *buffer_len; (*counter)++) {
        if (*counter == *buffer_len - 1) {
            *buffer_len *= 2;
            *text = (char**)realloc(*text, *buffer_len * sizeof(char*));
        }
        fgets(sentence, SENTENCE_BUFFER, stdin);
        (*text)[*counter] = strdup(sentence);
        if (!strncmp(sentence, FIN, CMP_LEN)) {
            free(sentence);
            break;
        }
    }
}

void regex_compile_test(char *regex_pattern, regex_t *regex_compiled) {
    if(regcomp(regex_compiled, regex_pattern, REG_EXTENDED)) {
        fprintf(stderr, "Error compiling regex: %s\n", regex_pattern);
        exit(1);
    }
}

void output_superusers_commands(char **text, size_t counter, regex_t *regex_compiled, regmatch_t *group_array) {
    for (size_t i = 0; i < counter; i++) {
        if (regexec(regex_compiled, text[i], MAX_GROUP, group_array, 0) == 0) {
            printf("%.*s - %.*s",
                    (int)(group_array[1].rm_eo - group_array[1].rm_so), text[i] + group_array[1].rm_so,
                    (int)(group_array[2].rm_eo - group_array[2].rm_so), text[i] + group_array[2].rm_so);
        }
        free(text[i]);
    }
}

int main() {
    char *sentence = (char*)malloc(SENTENCE_BUFFER * sizeof(char));
    char **text = (char**)malloc(TEXT_START_BUFFER * sizeof(char*));
    size_t buffer_len = TEXT_START_BUFFER;
    size_t counter;
    regex_t regex_compiled;
    regmatch_t group_array[MAX_GROUP];
    
    read_sentences(&text, sentence, &buffer_len, &counter);
    regex_compile_test(REGEX_PATTERN, &regex_compiled);
    output_superusers_commands(text, counter, &regex_compiled, group_array);
    regfree(&regex_compiled);
    free(text);
    return 0;
}