#include "max.h"

int max (int * data, char size) {
    int result = data[0];
    for (char i = 1; i < size; i++)
        result = (data[i] > result) ? data[i] : result;
    return result;
}
