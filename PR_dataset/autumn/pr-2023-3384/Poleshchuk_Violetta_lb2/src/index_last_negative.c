#include "index_last_negative.h"

int index_last_negative(int arr[100]){
    int res;
    for (int index = 99; index >= 0; index--){
        if(arr[index] < 0){
            return index;
	}
    }
} 
