#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char NULL_TERMINATOR = '\0';

char* get_text(int* text_size, int* punctuation_count) {
    int capacity = 1;
    char* text = (char*) malloc(sizeof(char));
    char ch = getchar();
    while (ch != '!') {
        text[(*text_size)++] = ch;
        if (*text_size >= capacity) {
            capacity *= 2;
            text = (char*) realloc(text, capacity * sizeof(char));
        }
        if (ch == '.' || ch == ';' || ch == '?') {
            (*punctuation_count)++;
        }
        ch = getchar();
    }
    text[*text_size] = NULL_TERMINATOR;
    return text;
}

void print_sentences(const char *text, int total_sentences) {
    const char *start = text;
    const char *end;
    int formatted_sentences = 0;

    while ((end = strpbrk(start, ".;?")) != NULL) {
        if (*end != '?') {
            while (*start == ' ' || *start == '\t') {
                start++;
            }
            for (const char *temp = start; temp <= end; temp++) {
                putchar(*temp);
            }
            putchar('\n');
            formatted_sentences++;
        }
        start = end + 1;
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d\n", total_sentences, formatted_sentences);
}

int main() {
    int text_size = 0;
    int n = 0; 
    char* text = get_text(&text_size, &n);

    if (text != NULL) {
        print_sentences(text, n);
    }

    free(text);
    return 0;
}
