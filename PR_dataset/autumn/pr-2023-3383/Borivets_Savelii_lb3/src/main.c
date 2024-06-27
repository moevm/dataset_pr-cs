#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    int N = 20, M = 20;
    char **mas = (char **) malloc(sizeof(char *) * N);
    int countn = 0;//счетчик предложений
    for (int i = 0;; i++) {
        countn++;
        mas[i] = (char *) malloc(sizeof(char) * M);
        char ch = getchar();
        while (ch == '\n' || ch == ' ' || ch == '\t') {
                ch = getchar();
        }
        int count_ch = 0;//счетчик символов в предложении
        for (int k = 0;(ch != '?') && (ch != ';') && (ch != '!') && (ch != '.'); k++) {
                mas[i][k] = ch;
                count_ch++;
                ch = getchar();
                if (k == M - 1) {
                        M += 20;
                        mas[i] = (char *) realloc(mas[i], sizeof(char) * M);
                }
                if (ch == '\n') {
                        ch = getchar();
                }

        }
        mas[i][count_ch] = ch;
        mas[i][count_ch + 1] = '\0';
        if (!strcmp(mas[i], "Dragon flew away!\0")) {
                break;
        }
        if (i == N - 1) {
            N += 20;
            mas = (char **) realloc(mas, sizeof(char *) * N);
        }
    }
    int cnt555 = 0;//счетчик 555
    for (int i = 0; i < countn; i++) {
            if (strstr(mas[i], " 555 ") || strstr(mas[i], "555 ") == &mas[i][0] || strstr(mas[i], " 555.") || strstr(mas[i], " 555?") || strstr(mas[i], " 555;")) {
                    cnt555++;
            } else {
                    printf("%s\n", mas[i]);
            }
    }
    countn--;
    printf("Количество предложений до %d и количество предложений после %d", countn, countn - cnt555);
    for (int i = 0; i < N; i++) {
        free(mas[i]);
    }
    free(mas);
    return 0;
}
