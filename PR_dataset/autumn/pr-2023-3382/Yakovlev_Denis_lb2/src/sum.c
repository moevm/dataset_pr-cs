#include "sum.h"
#include "min.h"

int sum(int array[], int length) {
    int sum = 0, min = Min(array, length), j = 0;
    while (array[j] > Min) {
        sum += array[j];
        j++;
    }
    return sum;
}