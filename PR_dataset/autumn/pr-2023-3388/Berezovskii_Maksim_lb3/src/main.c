#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER 10000

void input_text (char * text) {
    char * str = malloc(MAX_BUFFER * sizeof(char));
    int i = 0;
    while (1) {
        fgets(str, MAX_BUFFER, stdin);
        int len = strlen(str);
        strncpy(text + i, str, len);
        i += len;
        if (strstr(str, "Dragon flew away!"))
            break;
    }
    free(str);
}

int count_sentences(const char *text) {
    int count = 0;
    while (*text) {
        if ((*text) == '.' || (*text) == ';' || (*text) == '?') {
            count++;
        }
        text++;
    }
    return count;
}

void del_tabs(char *str) {
    int len = strlen(str);
    int index = 0;
    while (str[index] == '\t' || str[index] == '\n' || str[index] == ' ') {
        index++;
    }
    if (index < len) {
        printf("%s\n", str + index);
    }
}


int count_uppercase(const char *sentence) {
    int count = 0;
    while (*sentence) {
        if (isupper((unsigned char)*sentence)) {
            count++;
        }
        sentence++;
    }
    return count;
}

void print_func(char * text, int *count_of_sentences_before, int *count_of_sentences_after) {
    input_text(text);

    *count_of_sentences_before = count_sentences(text);

    for (int i = 0; text[i]; i++) {
        if (text[i] == '.' || text[i] == ';' || text[i] == '?') {
            text[i+1] = '\n';
        }
    }

    const char* delimiters = "\n";
    char *sentence = strtok(text, delimiters);
    *count_of_sentences_after = 0;

    while (sentence != NULL) {
        if (count_uppercase(sentence) <= 1) {
            del_tabs(sentence);
            (*count_of_sentences_after)++;
        }
        sentence = strtok(NULL, delimiters);
    }
}

int main() {
    char * array[MAX_BUFFER];
    int count_of_sentences_before = 0, count_of_sentences_after = 0;

    print_func(array, &count_of_sentences_before, &count_of_sentences_after);

    printf("Количество предложений до %d и количество предложений после %d\n", count_of_sentences_before, count_of_sentences_after-1);

    return 0;
}
