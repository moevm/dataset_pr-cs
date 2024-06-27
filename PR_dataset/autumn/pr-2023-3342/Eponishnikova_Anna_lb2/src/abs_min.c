#include "abs_min.h"
int abs_min(int array[], int length)
{
    int abs_min = 100000;
    for(int i = 0; i < length; i++){
        if (abs(array[i]) < abs(abs_min)){
            abs_min = array[i];
        }
    }
    return abs_min;
}