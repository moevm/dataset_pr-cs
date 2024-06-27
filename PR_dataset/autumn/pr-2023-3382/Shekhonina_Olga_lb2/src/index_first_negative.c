#include "index_first_negative.h"

int index_first_negative(int arr[], int size){
    int ind;
    for (int i = 0;i<size;i++){
        if (arr[i]<0){
            ind = i;
            break;
        }
    }
    return ind;
}
