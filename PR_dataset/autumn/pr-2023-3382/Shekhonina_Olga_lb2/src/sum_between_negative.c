#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int arr[], int size){
    int ind1 = index_first_negative(arr, size);
    int ind2 = index_last_negative(arr, size);
    int sum = 0;
    for (int i = ind1; i<ind2; i++){
        sum+=abs(arr[i]);
    }
    return sum;
}
