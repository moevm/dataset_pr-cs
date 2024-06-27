#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 40
#define TERM '!'

char** text_input(int* count_sentence_before) {
    int sentence_len = 0;
    int sentence_count = 0;
    int text_size = SIZE;
    int sentence_size = SIZE;

    char** text = (char**)malloc(sizeof(char*) * text_size);
    char* sentence = (char*)malloc(sizeof(char) * sentence_size);

    char current_symbol;
    do {
        current_symbol = getchar();
        if (current_symbol == '\n') {
            continue;
        }

        sentence[sentence_len++] = current_symbol;
        if (sentence_size <= sentence_len) {
            sentence_size += SIZE;
            sentence = realloc(sentence, sizeof(char) * sentence_size);
            if (sentence == NULL) {
                printf("Memory allocation error!");
                exit(1);
            }
        }

        if (current_symbol == '!' || current_symbol == '.' || current_symbol == ';' || current_symbol == '?') {
            sentence[sentence_len] = '\0';
            if (sentence[0] == ' ') {
                memmove(sentence, sentence + 1, strlen(sentence));
            }

            text[sentence_count++] = strdup(sentence);
            sentence_size = SIZE;
            sentence_len = 0;
            if (text_size <= (sentence_count)) {
                text_size += SIZE;
                text = realloc(text, sizeof(char*) * text_size);
                if (text == NULL) {
                    printf("Memory allocation error!");
                    exit(1);
                }
            }
        }

    } while (current_symbol != TERM);
    *count_sentence_before = sentence_count;
    return text;
}

int is_number(char* word) {
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
        if (isdigit(word[i])) {
            continue;
        }
        return 0;
    }
    return 1;
}

int sentence_check(char* sentence) {
    const char* sep = " ;.?";
    char* word = strtok(strdup(sentence), sep);

    while (word != NULL) {
        if (is_number(word) == 0) {
            for (int i = 1; i < strlen(word) - 1; i++) {
                if (isdigit(word[i])) {
                    return 0;
                }
            }
        }
        word = strtok(NULL, sep);
    }
    return 1;
}

void output(char** text, int count_sentence_before) {
    int count_sentence_after = 0;
    char* sentence;
    for (int i = 0; i < count_sentence_before; i++) {
        sentence = text[i];
        if (sentence_check(sentence)) {
            printf("%s\n", sentence);
            count_sentence_after++;
        }
    }
    printf("Количество предложений до %d и количество предложений после %d",
           count_sentence_before - 1, count_sentence_after - 1);
}

void clear_memory(char** text, int count_sentence_before){
    for (int i = 0; i < count_sentence_before; i++) {
        free(text[i]);
    }
    free(text);
}

int main() {
    int count_sentence_before = 0;
    char** text = text_input(&count_sentence_before);

    output(text, count_sentence_before);
    clear_memory(text, count_sentence_before);
    
    return 0;
}