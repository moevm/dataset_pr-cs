#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция для сравнения строк
int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

// Функция для поиска слова в тексте в отсортированном тексте
int serge(char **arr, int begin, int end, char *word) {
    while (begin <= end) {
        int mid = begin + (end - begin) / 2; //середина отрезка 

        int res = strcmp(arr[mid], word);// посимвольное сравнение строк

        if (res == 0) {//совпадение строк
            return 1;
        }

        if (res < 0) {
            begin = mid + 1;//сдвиг отрезка вправо
        } else {
            end = mid - 1;//сдвиг отрезка влево
        }
    }

    return 0;//не нашли слова в тексте
}

int main() {
    char text[1000];//для считывания текста
    char str[30];//для считывания слова

    // Ввод текста и слова
    fgets(text, sizeof(text), stdin);
    scanf("%s", str);

    // Разбиение текста на слова
    char *words[1000];
    int i = 0;

    char *c = strtok(text, " .");//текущее слово
    while (c != NULL) {
        words[i] = c;
        i++;
        c = strtok(NULL, " .");
    }

    // Сортировка слов
    qsort(words, i, sizeof(char *), cmp);

    // Поиск слова в тексте
    int answer = serge(words, 0, i - 1, str);

    // Вывод результата
    if (answer) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }

    return 0;
}

