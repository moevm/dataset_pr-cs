#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Функция сравнения для сортировки
int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b); // функция сравнения строк
}

// Функция для проверки наличия слова в тексте
int Search_Word(const char* word, const char* const* text, int Text_Length) {
    const char** result = bsearch(&word, text, Text_Length, sizeof(const char*), compare); // функция двоичного поиска
    
    if (result != NULL)
        return 1; // Слово найдено
    else
        return 0; // Слово не найдено
}

int main() {

    char text[1001]; // Исходный текст
    char str[31]; // Искомое слово
    
    fgets(text, sizeof(text), stdin); // Считываем текст
    text[strcspn(text, "\n")] = '\0'; 
    
    fgets(str, sizeof(str), stdin); // Считываем слово
    str[strcspn(str, "\n")] = '\0'; 
    
    const int Max_Text = 1000; // Маскимальная длина текста
    const char* words[Max_Text]; // Массив слов текста
    int Word_Count = 0; // Счетчик слов
    
    //  Разбиение тескта на слова
    char* word = strtok(text, " .");
    while (word != NULL && Word_Count < Max_Text) {
        words[Word_Count] = word;
        word = strtok(NULL, " .");
        Word_Count++;
    }
    
    // Сортировка слов 
    qsort(words, Word_Count, sizeof(const char*), compare);
    
    // Поиск слова в тексте
    int result = Search_Word(str, words, Word_Count);
    
    // Вывод результата
    if (result)
        printf("exists\n");
    else
        printf("doesn't exist\n");

    return 0;
} 
