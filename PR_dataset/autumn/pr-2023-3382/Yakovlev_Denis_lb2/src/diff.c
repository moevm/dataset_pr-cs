#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int array[], int length) {
    return max(array, length) - min(array, length);
}