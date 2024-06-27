#include “abs_max.h”
int abs_max(int array[], int length)
{   
    int abs_max = 0;
    for(int i = 0; i < length; i++){
        if (abs(array[i]) > abs(abs_max)){
            abs_max = array[i];
            
        }
    }
    return abs_max;
}