# include "index_last_negative.h"

int index_last_negative(int arr[], int amount){
    int x = 0;
    for (int i = amount - 1; i >= 0; i--){
        if (arr[i] < 0) {
            x = i;
            break;
        }    
    }
    return x;
}