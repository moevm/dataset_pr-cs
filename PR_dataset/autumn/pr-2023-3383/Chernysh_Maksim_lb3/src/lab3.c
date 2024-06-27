#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int equal_str(char const *str1, char const *str2) {
    if (strlen(str1) != strlen(str2))
        return 0;
    else {
        for (int i = 0; i < strlen(str1); i++) {
            if (str1[i] != str2[i])
                return 0;
        }
    }
    return 1;
}


char *read_sentence() {
    char ch;
    int size = 200;
    int actual_size = 0;
    char *sentence = malloc(size * sizeof(char));
    do {
        if (size == actual_size) {
            size += 100;
            sentence = realloc(sentence, size);
        }
        ch = (char) getchar();
        sentence[actual_size++] = ch;
    } while (ch != '.' && ch != ';' && ch != '?' && ch != '!');
    sentence[actual_size] = '\0';
    return sentence;
}


char *format_sentence(char *sentence) {
    while (sentence[0] == '\t' || sentence[0] == ' ' || sentence[0] == '\n') {
        for (int i = 0; i < strlen(sentence)+1; i++)
            sentence[i] = sentence[i + 1];
    }
    return sentence;
}


char **read_text(int *length) {
    int size = 200;
    int actual_size = 0;
    char *check_str = "Dragon flew away!";
    char *sentence;
    char **text = malloc(size * sizeof(char *));
    do {
        sentence = read_sentence();
        format_sentence(sentence);
        if (size <= actual_size) {
            size += 100;
            text = realloc(text, size);
        }
        text[*length] = sentence;
        *length += 1;
        actual_size += (int) strlen(sentence);
    } while (equal_str(sentence, check_str) == 0);
    return text;
}


void print_sentence(char *sentence) {
    for (int i = 0; i < strlen(sentence); i++) {
        printf("%c", sentence[i]);
    }
}


void print_text(char **text, int txt_len) {
    for (int i = 0; i < txt_len; i++) {
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
    char **new_txt = malloc(prev_len * sizeof(char *));
    for (int i = 0; i < prev_len; i++) {
        int *in_index = malloc(200 * sizeof(int));
        int res = del_numb(prev_text[i]);
        if (res == 0) {
            new_txt[*new_len] = prev_text[i];
            ++*new_len;
        } else
            free(prev_text[i]);
        free(in_index);
    }
    return new_txt;
}


void free_text(char **text, int txt_len) {
    for (int i = 0; i < txt_len; i++)
        free(text[i]);
    free(text);
}


int main() {
    int txt_len = 0;
    char **text = read_text(&txt_len);
    int new_len = 0;
    char **new_txt = copy_text(text, txt_len, &new_len);
    print_text(new_txt, new_len);
    printf("Количество предложений до %d и количество предложений после %d\n", txt_len - 1, new_len - 1);
    free_text(new_txt, new_len);
    return 0;
}
