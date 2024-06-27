#include "sum.h"
#include "min.h"

int getSum(int arr[], int length) {
    int min = getMin(arr, length);
    int i = 0, sum = 0;
    while (arr[i] != min) {
        sum += arr[i];
        i++;
    }
    return sum;
}