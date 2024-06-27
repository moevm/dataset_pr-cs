#include "index_first_negative.h"
#define N 100

int arr[N];

int index_first_negative (int a[]){
    for (int i = 0; i < N; i++) {
        if (arr[i] < 0){
            return i;
            break;
        }
    }
    return -1;
}