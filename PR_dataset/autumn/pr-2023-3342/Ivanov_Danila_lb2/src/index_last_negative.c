#include "index_last_negative.h"

int index_last_negative(int arr[], int N){
    for (int j = N - 1; j >= 0; j--){
        if (arr[j] < 0){
            return j;
        }
    }
}