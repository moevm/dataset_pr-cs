#include <stdlib.h>
#include "sum.h"
unsigned long sum(int* array, unsigned int start, unsigned int end) {
    unsigned long result = 0;
    for (unsigned int i = start; i <= end; i++)
        result += abs(array[i]);
    return result;
}
