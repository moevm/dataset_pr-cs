#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

#define N 100

int main() {

    //количество предложений до и после
    int n = 0;
    int m = 0;
    int kol = 0;
    int len = 0;
    int capacity_kol = N;
    int capacity_len = N;
    char c;

    //создание динамического массива строк и ввод
    char** sentences = malloc(N * sizeof(char*));
    for (int i = 0; i < INT_MAX; i++) {
        kol++;
        if (kol >= capacity_kol) {
            capacity_kol += N;
            sentences = realloc(sentences, capacity_kol * sizeof(char*));
            if (sentences == NULL)
                exit(1);
        }
        sentences[i] = malloc(capacity_len * sizeof(char));
        for (int j = 0; j < INT_MAX; j++) {
            c = getchar();
            sentences[i][j] = c;
            len++;
            if (len >= capacity_len) {
                capacity_len += N;
                sentences[i] = realloc(sentences[i], capacity_len * sizeof(char*));
                if (sentences[i] == NULL)
                    exit(1);
            }
            //если конец строки, добавление \0 и выход из цикла заполнения i строки
            if (c == '.' | c == ';' | c == '?' | c == '!') {
                sentences[i][j + 1] = '\0';
                break;
            }
        }
        n++;
        int k;
        //удаление табуляции, пробелов и переноса строки в начале предложения
        while (isspace(sentences[i][0])) {
            k = 0;
            while (k < strlen(sentences[i])) {
                sentences[i][k] = sentences[i][k + 1];
                k++;
            }
        }
        char* end = "Dragon flew away!";
        //break, если предложение Dragon flew away!
        if (!strcmp(sentences[i], end))
            break;
    }

    //удаление строк с числом 555
    m = n;
    for (int i = 0; sentences[i] != 0; i++)                    //пока не кончатся предложения
        for (int j = 0; j < strlen(sentences[i]) - 3; j++)       //без символов конца строк
            if (sentences[i][j] == '5' && sentences[i][j + 1] == '5' && sentences[i][j + 2] == '5')
                if ((j == 0 && sentences[i][j + 3] == ' ') |                       //555 в начале строки
                    (sentences[i][j - 1] == ' ' && sentences[i][j + 3] == ' ') |        //555 в середине строки
                    (sentences[i][j - 1] == ' ' && sentences[i][j + 4] == '\0')) {       //555 в конце строки
                    //если нашлась такая строка, она удаляется, все последующие строки переносятся 
                    for (int k = i; k < m; k++)
                        sentences[k] = sentences[k + 1];
                    //i-- для перехода на следующую строку, количество предложений m уменьшается
                    i--;
                    m--;
                    break;
                }

    //вывод предложений
    for (int i = 0; i < m; i++)
        printf("%s\n", sentences[i]);
    printf("Количество предложений до %d и количество предложений после %d\n", n - 1, m - 1);

    //освобождение памяти
    for (int i = 0; sentences[i] != 0; i++)
        free(sentences[i]);
    free(sentences);
    return 0;

}