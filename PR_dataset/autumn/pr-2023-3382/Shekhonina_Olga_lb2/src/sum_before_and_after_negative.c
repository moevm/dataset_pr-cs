#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int arr[], int size){
    int sum = 0;
    int ind1 = index_first_negative(arr, size);
    int ind2 = index_last_negative(arr, size);
    for (int i = 0; i<ind1; i++){
	   sum+=abs(arr[i]);
    }
    for (int i = ind2; i<size; i++){
	    sum+=abs(arr[i]);
    }
    return sum;
}
