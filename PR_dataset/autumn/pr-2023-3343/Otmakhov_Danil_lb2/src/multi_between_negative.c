#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[], int sizeOfArr){
    int product_1 = 1;
    for (int i = index_first_negative(arr, sizeOfArr); i < index_last_negative(arr, sizeOfArr); i++){
        product_1 = product_1 * arr[i];
    }
    return product_1;
}
