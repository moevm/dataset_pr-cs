#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IS_IN "exists"
#define IS_NOT_IN "doesn't exist"
#define WORD_DELIMS ". \f\n\r\t\v" // разделители по заданию + пробельные символы
#define BLOCK_SIZE 10

void read_text(char **text, size_t *text_size);
void split_to_words(char **source_text, char ***splitted_text, size_t *splitted_size);
int compare_qsort(const void *a, const void *b);
int compare_bsearch(const void *a, const void *b);

int main()
{
    char *text;
    size_t text_size;
    read_text(&text, &text_size);

    char **words;
    size_t words_size;
    split_to_words(&text, &words, &words_size);

    char *key = words[--words_size]; // записываем в переменную последнее слово и уменьшаем размер массива

    qsort(words, words_size, sizeof(char *), compare_qsort);
    char **result = bsearch(key, words, words_size, sizeof(char *), compare_bsearch);
    if (result != NULL)
    {
        printf("%s\n", IS_IN);
    }
    else
    {
        printf("%s\n", IS_NOT_IN);
    }

    free(words);
    free(text);
    return 0;
}

void read_text(char **text, size_t *text_size) // считывание текста
{
    *text_size = 0;
    size_t text_capacity = BLOCK_SIZE;
    *text = (char *)malloc(text_capacity * sizeof(char));
    char ch = getchar();
    while (ch != EOF && ch != '\0') // поскольку в задании явно не указан признак конца текста, считываем текст до EOF или \0
    {
        (*text)[(*text_size)++] = ch;
        if (*text_size == text_capacity - 1)
        {
            text_capacity += BLOCK_SIZE;
            *text = (char *)realloc(*text, text_capacity * sizeof(char));
        }
        ch = getchar();
    }
    (*text)[*text_size] = '\0';
}
void split_to_words(char **source_text, char ***splitted_text, size_t *splitted_size) // разбиение текста на слова
{
    *splitted_text = (char **)malloc(1 * sizeof(char *));
    *splitted_size = 0;

    char *istr = strtok(*source_text, WORD_DELIMS);
    while (istr != NULL)
    {
        (*splitted_text)[(*splitted_size)++] = istr;
        *splitted_text = (char **)realloc(*splitted_text, (*splitted_size + 1) * sizeof(char *));
        istr = strtok(NULL, WORD_DELIMS);
    }
}
int compare_qsort(const void *a, const void *b) // сравнение строк для qsort
{
    const char *first = *((char **)a);
    const char *second = *((char **)b);
    return strcmp(first, second);
}
int compare_bsearch(const void *a, const void *b) // сравнение строк для bsearch
{
    const char *first = (char *)a;
    const char *second = *((char **)b);
    return strcmp(first, second);
}