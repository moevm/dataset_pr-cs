#include  "index_last_negative.h"

int index_last_negative(int arr[], int size){
    int ind;
    for (int i = size - 1;i>=0;i--){
        if (arr[i]<0){
            ind = i;
            break;
        }
    }
    return ind;
}
