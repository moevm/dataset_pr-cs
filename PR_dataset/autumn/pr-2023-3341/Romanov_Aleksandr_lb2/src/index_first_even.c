#include "index_first_even.h"
#include <stdlib.h>
int index_first_even (int arr[], int len){
    int res = 0;
    for (int i = 0; i<len; i++){
        if ((abs(arr[i]))%2==0){
            res = i;
            return res;
        }
    }
}
