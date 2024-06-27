#include <stdio.h>
#include <stdlib.h>
#define MAX_INPUT_LEN 100

int index_first_zero(int* array, unsigned int length) {
    for (unsigned int i = 0; i < length; i++) {
        if (array[i] == 0) {
            return i;
        }
    }
    return -1;
}

int index_last_zero(int* array, unsigned int length) {
    for (unsigned int i = length; i > 0; i--) {
        if (array[i-1] == 0) {
            return i - 1;
        }
    }
    return -1;
}

unsigned long sum(int* array, unsigned int start, unsigned int end) {
    unsigned long result = 0;
    for (unsigned int i = start; i <= end; i++)
        result += abs(array[i]);
    return result;
}

unsigned long sum_between(int* array, unsigned int length) {
    int first = index_first_zero(array, length);
    int last = index_last_zero(array, length);

    return sum(array, first+1, last-1);
}

unsigned long sum_before_and_after(int* array, unsigned int length) {
    return sum(array, 0, length-1) - sum_between(array, length);
}

void error() {
    printf("Данные некорректны\n");
    return;
}

void final(int f_output) {
    if (f_output == -1) error();
    else printf("%d\n", f_output);

    return;
}

int get_data(int* array, unsigned int* length) {
    (*length) = 0;
    int command = -1;

    scanf("%d", &command);
    unsigned int i = 0;
    do {
        scanf("%d", &array[i]);
        i++;
        (*length)++;
    } while (getchar() != '\n');
    return command;
}

int main() {
    int array[MAX_INPUT_LEN] = { 0 };
    unsigned int length = 0;
    int command = get_data(array, &length);

    switch (command) {
        case 0:
            final(index_first_zero(array, length));
            break;
        case 1:
            final(index_last_zero(array, length));
            break;
        case 2:
            final(sum_between(array, length));
            break;
        case 3:
            final(sum_before_and_after(array, length));
            break;
        default:
            error();
    }
    return 0;
}
