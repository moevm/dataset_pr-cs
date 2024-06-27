#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <regex.h>

#define BUFFER 1024
#define MAX_LEN 100
#define CHECK 3
#define GROUPS_ID 8

char* get_full_text(int*);
char** split_sentences(char*, int);
void check_regular(char**, int);


int main() {
    int sentences_count = 0;
    char* text = get_full_text(&sentences_count);
    //    printf("%s\n", text);
    //    printf("%d\n", sentences_count);
    char** separation_text = split_sentences(text, sentences_count);
    check_regular(separation_text, sentences_count);

    free(text);
    free(separation_text);
    return 0;
}

char* get_full_text(int* sentences_count) {
    char c;
    int i = 0;
    int capacity = BUFFER;
    char* text = (char*)calloc(capacity, sizeof(char));

    while ((c = getchar()) != EOF) {
        text[i] = c;
        if (c == '\n') {
            ++(*sentences_count);
        }
        if (i == capacity - 1) {
            capacity += BUFFER;
            text = realloc(text, capacity * sizeof(char));
        }
        if (i >= CHECK && text[i] == '.' && text[i - 1] == 'n' && text[i - 2] == 'i' && text[i - 3] == 'F') {
            break;
        }
        i++;
    }
    text[i - 4] = '\0';
    return text;
}

char** split_sentences(char* full_text, int count_sentences) {
    int length = 0;
    char** sentences = (char**)calloc(count_sentences, sizeof(char*));
    char* sentence = strtok(full_text, "\n");

    while (sentence != NULL) {
        if (length >= count_sentences) {
            count_sentences *= 2;
            sentences = realloc(sentences, sizeof(char*) * count_sentences);
        }
        sentences[length] = sentence;
        sentence = strtok(NULL, "\n");
        ++length;

    }
    return sentences;
}

void check_regular(char** sentences, int sentences_count) {
    char* regexString = "(\\w+\\:\\/\\/)?(www\\.)?(([a-z0-9\\.]+)?[a-z0-9]+\\.\\w+)\\/(([a-z0-9\\/]+)?\\w+\\/)?([a-z0-9]+\\.\\w+)";
    char** answer = (char**)calloc(sentences_count, sizeof(char*));
    regex_t regexCompiled;
    regmatch_t groups[GROUPS_ID];
    int size = 0;
    int matched_count = 0;
    regcomp(&regexCompiled, regexString, REG_EXTENDED);

    for (int j = 0; j < sentences_count; j++) {
        if (regexec(&regexCompiled, sentences[j], GROUPS_ID, groups, 0) == 0) {
            //answer = realloc(answer, sizeof(char*) * (matched_count+1));
            char* final_line = (char*)calloc(100, sizeof(char));
            size = 0;

            for (int i = groups[3].rm_so; i < groups[3].rm_eo; i++) {
                final_line[size] = sentences[j][i];
                ++size;
            }
            final_line[size++] = ' ', final_line[size++] = '-', final_line[size++] = ' ';
            for (int i = groups[7].rm_so; i < groups[7].rm_eo; i++) {
                final_line[size] = sentences[j][i];
                ++size;
            }

            final_line[size] = '\0';
            answer[matched_count++] = final_line;
        }
    }
    for (int i = 0; i < matched_count; i++) {
        if (i == matched_count - 1)
            printf("%s", answer[i]);
        else
            printf("%s\n", answer[i]);
    }
}