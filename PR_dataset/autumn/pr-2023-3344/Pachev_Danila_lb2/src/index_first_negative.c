#include "index_first_negative.h"
int index_first_negative_func(int arr[], int count){
    int first_negative_index;
    for (int i = 0;i<count;i++){
        if (arr[i]<0){
            first_negative_index = i;
            break;
        }
    }
    return first_negative_index;
}
