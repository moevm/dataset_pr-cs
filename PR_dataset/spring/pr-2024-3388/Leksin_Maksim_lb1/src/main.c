#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BUFFER_SIZE 1024
#define REGEX_STRING "([A-z0-9]+[A-z0-9_]*:\\/\\/)?(www.)?(([A-z0-9]+[A-z0-9_]*\\.)+([A-z]+))\\/([A-z0-9_]+\\/)*([A-z0-9_]+\\.[A-z0-9_]+)"
#define GROUP_COUNT 9
#define URL_GROUP_NUMBER 3
#define FILE_GROUP_NUMBER 7

char* input_text(int* len) {
    char* text = (char*)calloc(BUFFER_SIZE, sizeof(char));
    int current_size = BUFFER_SIZE;
    int i = 0;
    char c;

    while(1) {
        c = getchar();
        if (c == '\n' && i == 0) {
            continue;
        }
        text[i++] = c;
        if (i == current_size - 1) {
            current_size += BUFFER_SIZE;
            text = realloc(text, sizeof(char) * current_size);
        }
        if (c == '\n')
            (*len)++;
        if (strstr(text, "Fin."))
            break;
    }
    text[i-4] = '\0';
    return text;
}

char** split_into_sentences(char* text, int count) {
    char** sentences = (char**)calloc(count, sizeof(char*));
    int capacity = BUFFER_SIZE;
    int i = 0;

    char* sentence = strtok(text, "\n");
    while (sentence != NULL) {
        if (i >= capacity) {
            capacity *= 2;
            sentences = realloc(sentences, sizeof(char*) * capacity);
        }
        if (sentence[0] == ' ' || sentence[0] == '\t' || sentence[0] == '\n')
            sentence++;
        sentences[i++] = sentence;
        sentence = strtok(NULL, "\n");
    }
    return sentences;
}
void url_and_file_print() {
    regex_t regex;
    regcomp(&regex, REGEX_STRING, REG_EXTENDED);
    int total_sentences = 0;
    char *text = input_text(&total_sentences);
    char **sentences = split_into_sentences(text, total_sentences);
    regmatch_t group[GROUP_COUNT];
    for (int i = 0; i < total_sentences; i++) {
        if (regexec(&regex, sentences[i], GROUP_COUNT, group, 0) == 0) {
            for (int j = group[URL_GROUP_NUMBER].rm_so; j < group[URL_GROUP_NUMBER].rm_eo; j++)
                printf("%c", sentences[i][j]);
            printf(" - ");
            for (int j = group[FILE_GROUP_NUMBER].rm_so; j < group[FILE_GROUP_NUMBER].rm_eo; j++)
                printf("%c", sentences[i][j]);
            if (i < total_sentences - 1)
                printf("\n");
        }
    }
    regfree(&regex);
}

int main() {
    url_and_file_print();
}
