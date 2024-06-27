#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INIT_SIZE 200
#define DELTA 100


int str_comp(char const *first_str, char const *second_str) {
    if (strlen(first_str) != strlen(second_str))
        return 0;
    else {
        for (int i = 0; i < strlen(first_str); i++) {
            if (first_str[i] != second_str[i])
                return 0;
        }
    }
    return 1;
}

char *readSentence() {
    char symbol;
    int size = INIT_SIZE;
    int current_size = 0;
    char *sentence = malloc(size * sizeof(char));
    do {
        if (size == current_size) {
            size += DELTA;
            sentence = realloc(sentence, size);
        }
        symbol = (char) getchar();
        sentence[current_size++] = symbol;
    } while (symbol != '.' && symbol != ';' && symbol != '?' && symbol != '!');
    sentence[current_size] = '\0';
    return sentence;
}

char *fix_of_sentence(char *sentence) {
    while (sentence[0] == '\t' || sentence[0] == ' ' || sentence[0] == '\n') {
        for (int i = 0; i <= strlen(sentence); i++)
            sentence[i] = sentence[i + 1];
    }
    return sentence;
}

char **readText(int *length) {
    int size = INIT_SIZE;
    int current_size = 0;
    char *check = "Dragon flew away!";
    char *sentence;
    char **text = malloc(size * sizeof(char *));
    do {
        sentence = readSentence();
        fix_of_sentence(sentence);
        if (size <= current_size) {
            size += DELTA;
            text = realloc(text, size);
        }
        text[*length] = sentence;
        *length += 1;
        current_size += (int) strlen(sentence);
    } while (str_comp(sentence, check) == 0);
    return text;
}

void print_sentence(char *sentence) {
    for (int i = 0; i < strlen(sentence); i++) {
        printf("%c", sentence[i]);
    }
}

void print_txt(char **text, int text_len) {
    for (int i = 0; i < text_len; i++) {
        print_sentence(text[i]);
        printf("\n");
    }
}

int del_numb(char *sentence) {
    for (int i = 0; i < strlen(sentence) - 3; i++) {
        if (sentence[i] == '5' && sentence[i + 1] == '5' && sentence[i + 2] == '5' && isalnum(sentence[i - 1]) == 0 &&
            isalnum(sentence[i + 3]) == 0)
            return 1;
    }
    return 0;
}


char **copy_text(char **prev_text, int prev_len, int *new_len) {
    int index;
    char **new_txt = malloc(prev_len * sizeof(char *));
    for (index = 0; index < prev_len; index++) {
        int *in_index = malloc(INIT_SIZE * sizeof(int));
        int res = del_numb(prev_text[index]);
        if (res == 0) {
            new_txt[*new_len] = prev_text[index];
            ++*new_len;
        } else
            free(prev_text[index]);
        free(in_index);
    }
    return new_txt;
}

void free_txt(char **text, int text_len) {
    for (int i = 0; i < text_len; i++)
        free(text[i]);
    free(text);
}

int main() {
    int text_len = 0;
    char **text = readText(&text_len);
    int new_len = 0;
    char **new_txt = copy_text(text, text_len, &new_len);
    print_txt(new_txt, new_len);
    printf("Количество предложений до %d и количество предложений после %d\n", text_len - 1, new_len - 1);
    free_txt(new_txt, new_len);
    return 0;
}
