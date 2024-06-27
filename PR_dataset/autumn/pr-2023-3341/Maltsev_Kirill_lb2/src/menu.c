#include <stdio.h>

#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

#define ARR_SIZE 100

const char* num_output = "%d\n";

void get_input(char*, int*, int[]);
void allocator(char, int[], int);

int main() {
    char type;
    int array[ARR_SIZE];
    int size = 0;

    get_input(&type, &size, array);
    allocator(type, array, size);
    return 0;
}

void get_input(char* type, int* size, int array[]) {
    scanf("%c", type);
    while (getchar() != '\n') {
        scanf("%d", &array[(*size)++]);
    }
}

void allocator(char type, int array[], int size) {
    switch(type) {
    case '0':
        printf(num_output, index_first_even(array, size));
        break;
    case '1':
        printf(num_output, index_last_odd(array, size));
        break;
    case '2':
        printf(num_output, sum_between_even_odd(array, size));
        break;
    case '3':
        printf(num_output, sum_before_even_and_after_odd(array, size));
        break;
    default:
        printf("Данные некорректны\n");
    }
}
