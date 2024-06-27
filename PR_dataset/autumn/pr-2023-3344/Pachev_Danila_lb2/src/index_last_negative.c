#include "index_last_negative.h"

int index_last_negative_func(int arr[],int count){
    int last_negative_index;
    for (int i = count;i>=0;i--){
        if (arr[i]<0){
            last_negative_index = i;
            break;
        }
    }
    return last_negative_index;
}
