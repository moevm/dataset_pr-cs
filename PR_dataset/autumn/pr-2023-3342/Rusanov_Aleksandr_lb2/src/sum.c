#include "sum.h"

int sum(int arr[], int size, int index){
    int sum = 0;
    for (int k = index; k < size; k++ ){
        sum += arr[k];
    }
    return sum;
}
