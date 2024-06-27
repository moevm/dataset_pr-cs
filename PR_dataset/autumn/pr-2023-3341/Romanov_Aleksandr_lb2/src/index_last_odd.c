#include "index_last_odd.h"
#include <stdlib.h>
int index_last_odd (int arr[],int len){
    int res = 0;
    for (int i=0; i<len; i++){
        if ((abs(arr[i]))%2==1){
            res = i;
        }

    }
    return res;
}
