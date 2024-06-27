# include "index_first_negative.h"

int index_first_negative(int arr[], int amount) {
    int x = 0;
    for (int i = 0; i < amount; i++){
        if (arr[i] < 0) {
            x = i;
            break;
        }
    }
    return x;
}