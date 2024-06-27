#include "diff.h"
#include "max.h"
#include "min.h"

int getDiff(int arr[], int length) {
    return getMax(arr, length) - getMin(arr, length);
}