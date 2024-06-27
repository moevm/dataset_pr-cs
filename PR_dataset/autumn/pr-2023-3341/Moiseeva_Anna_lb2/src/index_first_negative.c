#include "index_first_negative.h"

int index_first_negative(int arr[], int arr_size){
    for (int j = 0; j < arr_size; j++){
       if (arr[j] < 0){
           return j;
       }
    }
}
