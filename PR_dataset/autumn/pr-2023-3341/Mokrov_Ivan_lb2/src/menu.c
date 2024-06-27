#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

// размер максимального массива
#define ARRAY_SIZE 20
#define INPUT_SIZE 50
#define out "%d\n"

int finite_array[ARRAY_SIZE]; // массив для обработки
int size; // Размер для обрабатываемого массива
char value; //  Код обработки

// Удаление пробелов, и запись массив в числовой параметр 
void clear_array(char array[], int finite_array[], int *size) {
    char *array_str;
    array_str = strtok(array, " ");
    array_str = strtok(NULL, " ");

    while (array_str != NULL) {
        finite_array[(*size)++] = atoi(array_str);
        array_str = strtok(NULL, " ");
    }
}

void input_data() {
     // ввод значения с терминала
    char received_array[INPUT_SIZE];
    fgets(received_array, INPUT_SIZE, stdin);

    // Отделения значения для запроса
    value = received_array[0];

    clear_array(received_array, finite_array, &size);
}

// Обработка массива по задоному коду и вывод на экран
void request_processing(int request) {
    switch(request) {
        case '0':
            printf(out, index_first_negative(finite_array, size));
            break;
        case '1':
            printf(out,index_last_negative(finite_array, size));
            break;
        case '2':
            printf(out,multi_between_negative(finite_array, size));
            break;
        case '3':
            printf(out,multi_before_and_after_negative(finite_array, size));
            break;
        default:
            printf("Данные некорректны");
            break;
    }
}

int main() {
    input_data();
    request_processing(value);
    return 0;
}
