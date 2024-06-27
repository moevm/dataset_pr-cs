#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* getText() {
    char* text = calloc(10, sizeof(char));
    char* p_start = text;
    char s, end = '!';
    int k = 0, c = 1;

    while ((s = getchar()) != end) {
        *p_start = s;
        p_start++;
        k++;
        if (k == 10 * c) {
            c++;
            text = realloc(text, sizeof(char) * (10 * c + 1));
            p_start = text + k;
        }
    }
    *p_start = '!';
    p_start++;
    *p_start = '\0';// Добавляем завершающий нулевой символ
    return text;
}

int main() {
    char* text = getText();
    char* p_start = text;
    char* p_end;
    int num_sen = 0, num_sen_end = -1;

    bool startOfSentence = true;

    for (int i = 0; text[i]; i++) {
        if (text[i] == '.' || text[i] == ';' || text[i] == '?') {
            num_sen++;
        }
        if (text[i] == '.' || text[i] == ';' || text[i] == '?' || text[i] == '!') {
            int found7 = 0;
            for (char* p = p_start; p <= text + i; p++) {
                if (*p == '7') {
                    found7 = 1;
                    break;
                }
            }
            if (!found7) {
                num_sen_end++;
                p_end = text + i;
                while (p_start <= p_end) {
                    if (startOfSentence && *p_start == ' ') {
                        p_start++;
                        continue;
                    }
                    if (*p_start != '\n') {
                        printf("%c", *p_start);
                    }
                    p_start++;
                    startOfSentence = false;
                }
                printf("\n");
            }
            startOfSentence = true;
            p_start = text + i + 1; // Сдвигаем указатель на начало следующего предложения
        } else if (text[i] != '\n' && text[i] != '\0' && text[i] != ' ' && p_start - 1 == p_end) {
            p_start = text + i; // Начинаем новое предложение
        }
    }
    printf("Количество предложений до %d и количество предложений после %d", num_sen, num_sen_end);

    free(text); // Освобождаем выделенную память
    return 0;
}
