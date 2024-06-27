#include "index_first_negative.h"

int index_first_negative(int arr[], int N){
    for (int i = 0; i < N; i++){
        if (arr[i] < 0){
            return i;
        }
    }
}