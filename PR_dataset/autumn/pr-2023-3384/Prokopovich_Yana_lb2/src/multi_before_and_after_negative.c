# include "multi_before_and_after_negative.h"
# include "index_first_negative.h"
# include "index_last_negative.h"

int multi_before_and_after_negative(int arr[], int amount){
    int n1 = index_first_negative(arr, amount);
    int n2 = index_last_negative(arr, amount);
    int x1 = 1, x2 = 1;
    for (int i = 0; i < n1; i++){
        x1 *= arr[i];
    }
    for (int i = n2; i < amount; i++){
        x2 *= arr[i];
    }
    return (x1 * x2);
}