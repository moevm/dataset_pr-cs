#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define SIZE_BUFFER 1024
#define NUM_OF_REGEX_GROUPS 4
#define REGEX_USER_NAME 1
#define REGEX_COMMAND_NAME 3
#define END_OF_TEXT len - 4

char *input_text(int *num_sentences) {
    char *text = malloc(SIZE_BUFFER * sizeof(char));
    int len = 0;
    char c;
    while (strstr(text, "Fin.") == 0) {
        c = getchar();
        text[len++] = c;
        if (c == '\n') {
            (*num_sentences)++;
        }
        if (len == SIZE_BUFFER) {
            text = realloc(text, SIZE_BUFFER*2);
            if (!text) return NULL;
        }
    }
    text[END_OF_TEXT] = '\0';
    return text;
}

char **text_sentences(char *text, int num_sentences) {
    char **sentences = malloc(num_sentences * sizeof(char *));
    if (!sentences) return NULL;

    int i = 0;
    char *sentence = strtok(text, "\n");
    while (sentence != NULL) {
        sentences[i++] = sentence;
        sentence = strtok(NULL, "\n");
    }
    return sentences;
}

void compile_and_match_regex(char **sentences, int num_sentences){
    regex_t regex;
    const char *pattern = "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+):[ +]?~[ +]?#[ +]?(.+)";
    regcomp(&regex, pattern, REG_EXTENDED);
    for (int i = 0; i < num_sentences; i++) {
        regmatch_t pmatch[NUM_OF_REGEX_GROUPS];
        if (regexec(&regex, sentences[i], NUM_OF_REGEX_GROUPS, pmatch, 0) == 0) {
            for (int z = pmatch[REGEX_USER_NAME].rm_so; z < pmatch[REGEX_USER_NAME].rm_eo; z++){
                printf("%c", sentences[i][z]);
            }
            printf(" - ");
            for (int w = pmatch[REGEX_COMMAND_NAME].rm_so; w < pmatch[REGEX_COMMAND_NAME].rm_eo; w++){
                printf("%c", sentences[i][w]);
            }
            printf("\n");
        }
    }
    regfree(&regex);
}

void process_text() {
    int num_sentences = 0;
    char *text = input_text(&num_sentences);
    char **sentences = text_sentences(text, num_sentences);
    if (sentences == NULL) {
        free(text);
        return;
    }
    compile_and_match_regex(sentences, num_sentences);
    free(text);
    free(sentences);
}

int main() {
    process_text();
    return 0;
}
