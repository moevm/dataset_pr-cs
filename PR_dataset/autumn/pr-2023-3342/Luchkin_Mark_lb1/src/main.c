#include <stdio.h>
#define MAX_SIZE  20


int index_first_negative(int *array, int array_size);
int index_last_negative(int *array, int array_size);
int multi_between_negative(int *array, int array_size);
int multi_before_and_after_negative(int *array, int array_size);

int main(void) {

    int num_solution;
    int array[MAX_SIZE];
    int array_size = 0;

    scanf("%d", &num_solution);
    while (getchar() != '\n') {
        scanf("%d", &array[array_size]);
        ++array_size;
    }

    switch (num_solution) {
    case 0:
        //index_first_negative
        printf("%d\n", index_first_negative(array, array_size));
        break;
    case 1:
        //index_last_negative
        printf("%d\n", index_last_negative(array, array_size));
        break;
    case 2:
        //multi_between_negative
        printf("%d\n", multi_between_negative(array, array_size));
        break;
    case 3:
        //multi_before_and_after_negative
        printf("%d\n", multi_before_and_after_negative(array, array_size));
        break;
    default:
        printf("%s\n", "Данные некорректны");
        break;
    }
    return 0;
}

int index_first_negative(int *array, int array_size) {
    for (int i = 0; i < array_size; ++i) {
        if (array[i] < 0) {
            return i;
        }
    }
    return -1;
}


int index_last_negative(int *array, int array_size) {
    for (int i = array_size - 1; i >= 0; --i) {
        if (array[i] < 0) {
            return i;
        }
    }
    return -1;
}

int multi_between_negative(int *array, int array_size) {
    int i = index_first_negative(array, array_size);
    int result = 1;
    for (i; i < index_last_negative(array, array_size); ++i) {
        result *= array[i];
    }

    return result;
}

int multi_before_and_after_negative(int *array, int array_size) {
    int index_last = index_last_negative(array, array_size);
    int index_first = index_first_negative(array, array_size);
    int result = 1;
    for (int i = 0; i < array_size; ++i) {
        if ((i < index_first) || (i >= index_last)) {
            result *= array[i];
        }
    }

    return result;
}
