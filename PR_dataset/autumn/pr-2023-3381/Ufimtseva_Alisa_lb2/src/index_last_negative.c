#include "index_last_negative.h"
#define N 100

int arr[N];

int index_last_negative (int a[]){
    for (int i=N-1; i>-1; i--){
        if (arr[i]<0){
            return i;
            break;
        }
    }
    return -1;
}