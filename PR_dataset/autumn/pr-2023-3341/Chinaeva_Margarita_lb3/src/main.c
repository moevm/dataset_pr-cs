#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100
#define END_STR '\0'

char read_str(char* str) {
    int size = STR_SIZE;
    int i = 0;
    do {
        if (i == size - 2) {
            size += STR_SIZE;
            str = (char*) realloc(str, size * sizeof(char));
        }
        char symbol = getchar();
        if (symbol != '\n' && symbol != '\t') {
            str[i] = symbol;
            i++;
        }
    } while (str[i - 1] != '.' && str[i - 1] != ';' && str[i - 1] != '?' && str[i - 1] != '!');
    str[i] = END_STR;
    return str[i - 1];
}

void processing(int* count_first, int* count_end) {
    char* new_str = malloc(STR_SIZE * sizeof(char));
    do {
        new_str = malloc(STR_SIZE * sizeof(char));
        char check = read_str(new_str);
        scanf("%*c");
        if (check != '?') {
            printf("%s\n", new_str);
            (*count_first)++;
            (*count_end)++;
        }
        else {
            (*count_first)++;
        }
    } while (strcmp(new_str, "Dragon flew away!") != 0);
    free(new_str);
}

int main() {
    int count_first = 0;
    int count_end = 0;
    processing(&count_first, &count_end);
    printf("Количество предложений до %d и количество предложений после %d\n", count_first - 1, count_end - 1);
    return 0;
}
