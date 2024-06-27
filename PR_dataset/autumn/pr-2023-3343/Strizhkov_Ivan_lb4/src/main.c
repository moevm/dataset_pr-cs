#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    char text[1000];
    char word[30];

    // Ввод текста и слова
    fgets(text, 1000, stdin);
    text[strcspn(text, "\n")] = '\0'; // Удаление символа новой строки

    fgets(word, 30, stdin);
    word[strcspn(word, "\n")] = '\0'; // Удаление символа новой строки

    // Разделение текста на слова
    char* words[1000];
    int wordCount = 0;
    char* token = strtok(text, " .");
    while (token != NULL) {
        words[wordCount] = token;
        wordCount++;
        token = strtok(NULL, " .");
    }

    // Сортировка слов
    qsort(words, wordCount, sizeof(char*), compare);

    // Бинарный поиск слова
    int found = 0;
    int left = 0;
    int right = wordCount - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(words[mid], word);
        if (cmp == 0) {
            found = 1;
            break;
        }
        else if (cmp < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    // Вывод результата
    if (found) {
        printf("exists\n");
    }
    else {
        printf("doesn't exist\n");
    }

    return 0;
}
