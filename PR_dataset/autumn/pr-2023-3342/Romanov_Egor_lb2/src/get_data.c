#include "get_data.h"

int get_data(int array[], int *array_length) {
    *array_length = 0;
    int program_mode;
    scanf("%d", &program_mode);
    while (getchar() != '\n') {
        scanf("%d", &array[*array_length]);
        (*array_length)++;
    }
    return program_mode;
}
