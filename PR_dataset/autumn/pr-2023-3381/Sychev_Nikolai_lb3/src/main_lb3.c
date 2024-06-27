#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 100
#define M 100

int main() {
    char** arr = malloc(N * sizeof(char*));
    if (arr == NULL) {
        fprintf(stderr, "Ошибка выделения памяти\n");
        return 0;
    }

    for (int i = 0; i < N; ++i) {
        char* test = malloc(M * sizeof(char));
        if (test == NULL) {
            fprintf(stderr, "Ошибка выделения памяти\n");
            for (int j = 0; j < i; j++) {
                free(arr[i]);
            }
            free(arr);
            return 0;
        }
        arr[i] = test;
    }

    char cymbol;
    int i = 0;
    int max_count_string = N;
    int count_string_before = 0;
    while (cymbol != '!') {
        int j = 0;
        int max_len_string = M;
        cymbol = getchar();
        while (cymbol != '!' && cymbol != '.' && cymbol != '?' && cymbol != ';') {
            if (cymbol == '\n') {
                cymbol = ' ';
            }

            if (j > 0 || (j == 0 && !isspace(cymbol))) {
                arr[i][j] = cymbol;
                j++;
            }

            cymbol = getchar();
            if (j % M == M - 1) {
                char* test = arr[i];
                max_len_string += M;
                test = realloc(arr[i], max_len_string * sizeof(char));
                if (test == NULL) {
                    fprintf(stderr, "Ошибка выделения памяти\n");
                    for (int l = 0; l < max_count_string; l++) {
                        free(arr[l]);
                    }
                    free(arr);
                    return 0;
                }
                arr[i] = test;
            }
        }
        arr[i][j] = cymbol;
        arr[i][j + 1] = '\0';
        int string_to_delete = 0;
        for (int k = 0; k < j; ++k) {
            if (k > 0 && isdigit(arr[i][k]) && isalpha(arr[i][k - 1]) && arr[i][k + 1] != ' ' && arr[i][k + 1] != '?' && arr[i][k + 1] != ';' && arr[i][k + 1] != '.') {
                string_to_delete++;
            }
        }
        if (string_to_delete == 0) {
            i++;
            if (i % N == 0) {
                max_count_string += N;
                char** test = arr;
                test = realloc(arr, max_count_string * sizeof(char*));
                if (test == NULL) {
                    fprintf(stderr, "Ошибка выделения памяти\n");
                    for (int l = 0; l < max_count_string; l++) {
                        free(arr[l]);
                    }
                    free(arr);
                    return 0;
                }
                arr = test;
                for (int p = i; p < max_count_string; p++) {
                    char* test1;
                    test1 = malloc(M * sizeof(char));
                    if (test1 == NULL) {
                        fprintf(stderr, "Ошибка выделения памяти\n");
                        for (int l = 0; l < p; l++) {
                            free(arr[l]);
                        }
                        free(arr);
                        return 0;
                    }
                    arr[p] = test1;
                }
            }
        }
        count_string_before++;
    }
    for (int w = 0; w < max_count_string; w++) {
        if (w < i) {
            puts(arr[w]);
        }
        free(arr[w]);
    }
    printf("Количество предложений до %d и количество предложений после %d", count_string_before - 1, i - 1);
    free(arr);
    return 0;
}
