#include <stdio.h>
#include "io_routine.h"

int get_data(int* array, unsigned int* length) {
    *length = 0;
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

void error() {
    printf("Данные некорректны\n");
    return;
}

void answer(int f_output) {
    if (f_output == -1) error();
    else printf("%d\n", f_output);

    return;
}
