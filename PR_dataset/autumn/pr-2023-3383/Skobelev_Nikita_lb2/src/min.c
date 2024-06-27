#include <stdio.h>
#include "min.h"
typedef int ll;
int min(int array[], int cnt, int task){
    ll index_min=0;
    for(ll i=0;i<cnt;++i){
        if(array[index_min]>array[i])index_min=i;
    }
    if(task == 1){
        printf("%d\n",array[index_min]);
        return 0;
    }
    else return index_min;
}