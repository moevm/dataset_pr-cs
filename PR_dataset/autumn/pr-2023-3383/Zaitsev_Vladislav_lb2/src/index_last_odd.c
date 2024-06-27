#include "index_last_odd.h"

int index_last_odd(int arr[], int len){
    int answer = 0;
    int i;
    for (i = 0; i < len; i++){
        if (arr[i] % 2 != 0){
            answer = i;
        }
    }
    return answer;
};


