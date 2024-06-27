#ifndef SORT_BY_LOWERCASE
#define SORT_BY_LOWERCASE
int countLowerCase(char *sentence); // считает кол-во строчных букв
void sortSentences(char **sentences, int *count); // сортировка предложений
int compare(const void *sentence1, const void *sentence2); // функция-компоратор
#endif