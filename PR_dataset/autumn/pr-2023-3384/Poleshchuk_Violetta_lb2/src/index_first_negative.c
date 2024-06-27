#include "index_first_negative.h"
int index_first_negative(int arr[100]){
    for (int index = 0; index < 100; index++){
        if(arr[index] < 0){
            return index;
        }
    }
}
