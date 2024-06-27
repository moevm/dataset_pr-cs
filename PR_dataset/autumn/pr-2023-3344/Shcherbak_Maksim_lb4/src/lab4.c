#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// сравнение строк при сортировке
int compare_bin(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {

    int dlina = 0;
 // ввод 
    char text[1000];
    fgets(text, 1000, stdin);

    char* to_find = malloc(30 * sizeof(char));
    fgets(to_find, 30, stdin);
    // разбиение текста на слова
    char** sentences = malloc(1 * sizeof(char*));

    char* word = strtok(text, " .!");

    while (word != NULL) {
        sentences[dlina++] = word;
        sentences = realloc(sentences, (dlina + 1) * sizeof(char*));
        word = strtok(NULL, " .!\0");
    }
    // сортировка слов
    qsort(sentences, dlina, sizeof(char*), compare_bin);
    // двоичный поиск слова
    char** result = (char**) bsearch(&to_find, sentences, dlina, sizeof(sentences[0]), compare_bin);

    if (result != NULL) {
        printf("exists");
    } else {
        printf("doesn't exist");
    }

    return 0;
}