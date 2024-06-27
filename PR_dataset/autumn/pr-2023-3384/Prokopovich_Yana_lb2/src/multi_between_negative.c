# include "multi_between_negative.h"
# include "index_first_negative.h"
# include "index_last_negative.h"

int multi_between_negative(int arr[], int amount){
    int n1 = index_first_negative(arr, amount);
    int n2 = index_last_negative(arr, amount);
    int x = 1;
    for (int i = n1; i < n2; i++){
        x *= arr[i];
    }
    return x;
}