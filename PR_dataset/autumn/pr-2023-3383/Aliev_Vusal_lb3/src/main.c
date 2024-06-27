#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 20

int main() {
    int length = SIZE, width = SIZE;
    char** text = malloc(sizeof(char*) * length);
    char symbol;
    int count_sent = 0, count_all = 0;

    for (int N = 0;; N++) {
        text[N] = malloc(sizeof(char) * width);

        symbol = getchar();
        while (symbol == ' ' || symbol == '\t') {
            symbol = getchar();
        }

        int M = 0;
        for (;; M++) {

            if (M > width - 1) {
                width *= 2;
                text[N] = realloc(text[N], sizeof(char) * width);
            }

            text[N][M] = symbol;
            symbol = getchar();

            if (symbol == '.' || symbol == ';' || symbol == '?') {
                count_all++;
                text[N][M + 1] = symbol;
                text[N][M + 2] = '\0';
                if (symbol != '?')
                    count_sent++;
                break;
            }

            if (symbol == '!') {
                text[N][M + 1] = symbol;
                text[N][M + 2] = '\0';
                break;
            }
        }

        if (N > length - 1) {
            length *= 2;
            text = realloc(text, sizeof(char*) * length);
        }

        if (text[N][M + 1] != '?')
            printf("%s\n", text[N]);

        if (strcmp(text[N], "Dragon flew away!") == 0) {
            printf("Количество предложений до %d и количество предложений после %d", count_all, count_sent);
            break;
        }
    }

    for (int i = 0; i < length; i++) {
        free(text[i]);
    }
    free(text);
    return 0;
}
