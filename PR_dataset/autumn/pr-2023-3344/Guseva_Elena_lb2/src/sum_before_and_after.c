#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int array[], int size){
    int sum = 0;
    int indx_1_0=index_first_zero(array, size);
    int indx_last_0=index_last_zero(array, size);
    for (int i=0; i<indx_1_0; i++){
        sum=sum+abs(array[i]);
        }
    for (int i=indx_last_0 + 1; i<size; i++){
        sum=sum+abs(array[i]);
    }
    return sum;
}
