#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int index_first_even(int array[], int size) {
    for (int i = 0; i < size; i++) {
        if (array[i] % 2 == 0) {
            return i;
        }
    }
    return -1; // Если нет четных элементов
}

int index_last_odd(int array[], int size) {
    for (int i = size - 1; i >= 0; i--) {
        if (array[i] % 2 != 0) {
            return i;
        }
    }
    return -1; // Если нет нечетных элементов
}

int sum_between_even_odd(int array[], int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += abs(array[i]);
    }
    return sum;
}

int sum_before_even_and_after_odd(int array[], int size, int start, int end) {
    int sum = 0;
    
    for (int i = 0; i < start; i++) {
        sum += abs(array[i]);
    }
    
    for (int i = end; i < size; i++) {
        sum += abs(array[i]);
    }
    
    return sum;
}


int main() {
    int choice;
    scanf("%d", &choice);
    
    int array[100];
    int size = 0;
    int num;

    // Считываем строку
    char input[256]; // Максимальная длина строки
    fgets(input, sizeof(input), stdin);

    // Разбиваем строку на числа
    char *token = strtok(input, " \n"); // Разделители - пробел и символ новой строки
    while (token != NULL) {
        num = atoi(token); // Преобразуем строку в целое число
        array[size++] = num;
        token = strtok(NULL, " \n");
    }

    switch (choice) {
        case 0:
            printf("%d\n", index_first_even(array, size));
            break;
        case 1:
            printf("%d\n", index_last_odd(array, size));
            break;
        case 2:
            {
                int start = index_first_even(array, size);
                int end = index_last_odd(array, size);
                printf("%d\n", sum_between_even_odd(array, start, end));
            }
            break;
        case 3:
            {
                int start = index_first_even(array, size);
                int end = index_last_odd(array, size);
                printf("%d\n", sum_before_even_and_after_odd(array, size, start, end));
            }
            break;
        default:
            printf("Данные некорректны\n");
    }

    return 0;
}