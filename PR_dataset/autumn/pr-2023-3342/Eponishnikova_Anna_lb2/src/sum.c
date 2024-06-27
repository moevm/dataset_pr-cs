#include "sum.h"
#include "abs_max.h"
int sum(int array[], int length)
{
    int sum = 0;
    int abs_maximum = abs_max(array,length);
    for(int i = 0;i <length; i++){
        if(array[i] == abs_maximum){
            for(int n = i; n < length;n++){
                sum += array[n];
            }
            return sum;
        }
    }
}