#include "sum.h"
#include "min.h"

long int sum (int * data, char size) {
    int minimum = min(data, size);
    long int result = 0;
    for (char i = 0; i<size; i++){
        if (data[i] == minimum)
            break;
        result += data[i];
    }
    return result;
}
