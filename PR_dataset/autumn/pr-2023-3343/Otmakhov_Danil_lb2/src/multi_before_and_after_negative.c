#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int sizeOfArr){
    int product_2 = 1;
    int i = 0;
    while (i < index_first_negative(arr, sizeOfArr)){
        product_2 = product_2 * arr[i];
        i++;
    }
    i = index_last_negative(arr, sizeOfArr);
    while (i < sizeOfArr){
        product_2 = product_2 * arr[i];
        i++;
    }
    return product_2;
}
