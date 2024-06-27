#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int array[], int actual_size_of_array) {
    for (int i = 0; i < actual_size_of_array; i++) {
        if (array[i] == 0) {
            return i;
        }
    }
}


int index_last_zero(int array[], int actual_size_of_array) {
    for (int i = actual_size_of_array-1; i >= 0; i--) {
        if (array[i] == 0) {
            return i;
        }
    }
}


int sum_between(int array[], int actual_size_of_array) {
    int sum = 0;
    for (int i = index_first_zero(array, actual_size_of_array) + 1; i < index_last_zero(array, actual_size_of_array); i++) {
        sum += abs(array[i]);
    }
    return sum;
}


int sum_before_and_after(int array[], int actual_size_of_array) {
    int sum = 0;
    for (int i = index_last_zero(array, actual_size_of_array)+ 1; i < actual_size_of_array; i++) {
        sum += abs(array[i]);
    }
    for (int i = 0; i < index_first_zero(array, actual_size_of_array); i++) {
        sum += abs(array[i]);
    }
    return sum;
}


int main(){
    int flag, actual_size_of_array;
    int array[100];
    char c;
    actual_size_of_array = 0;

    scanf("%d", &flag);
    scanf("%c", &c);
    while (c != '\n' && actual_size_of_array < 100) {
        scanf("%d", &array[actual_size_of_array]);
        scanf("%c", &c);
        actual_size_of_array += 1;
    }

    switch (flag)
    {
    case 0:
        printf("%i\n", index_first_zero(array, actual_size_of_array));
        break;
    case 1:
        printf("%i\n", index_last_zero(array, actual_size_of_array));
        break;
    case 2:
        printf("%i\n", sum_between(array, actual_size_of_array));
        break;
    case 3:
        printf("%i\n", sum_before_and_after(array, actual_size_of_array));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
    return 0;
}
