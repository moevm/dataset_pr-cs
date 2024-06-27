#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int count_uppercase_letters(const char *sentence) { //функция для оперделения количество заглавных 
    int count = 0;
    for (int i = 0; sentence[i] != '\0'; ++i) {
        if (isupper(sentence[i])) {
            count++;
        }
    }
    return count;
}
int main() {
    char *buffer = malloc(1);
    char *sentence = malloc(1);
    char c;
    int len = 0;
    int len_sent = 0;
    int is_start_of_sentence = 1;
    int count_before = 0;
    int count_after = 0;
    while ((c = getchar()) != EOF) {
        if (!(is_start_of_sentence && (c == ' ' || c == '\n' || c == '\t'))) {
            sentence[len_sent++] = c;
            sentence = realloc(sentence, len_sent + 2);
            sentence[len_sent] = '\0';
        }
        if (c == '.' || c == '?' || c == '!' || c == ';') {
            count_before++; // Подсчет предложений до обработки
            if (count_uppercase_letters(sentence) <= 1) { 
                for (int i = 0; i < len_sent; i++) {
                    buffer[len++] = sentence[i];
                    buffer = realloc(buffer, len + 2);
                    buffer[len] = '\0';
                }
                buffer[len++] = '\n';
                buffer = realloc(buffer, len + 2);
                buffer[len] = '\0';
                count_after++; // Подсчет предложений после обработки
            }
            len_sent = 0;
            is_start_of_sentence = 1;
        } else {
            is_start_of_sentence = 0;
        }
        if (strstr(sentence, "Dragon flew away!") != NULL) break;
    }
    if (strstr(buffer, "Dragon flew away!\n") != NULL) {
        count_after--; 
    }
    printf("%sКоличество предложений до %d и количество предложений после %d\n", buffer, count_before-1, count_after);
    free(buffer);
    free(sentence);
    return 0;
}
