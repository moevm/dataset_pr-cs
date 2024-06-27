#include <stdio.h>
#include "max.h"
typedef int ll;
ll max(ll array[], ll cnt, ll task){
    ll index_max=0;
    for(ll i=0;i<cnt;++i){
        if(array[index_max]<array[i])index_max=i;
    }
    if(task == 0){
        printf("%d\n",array[index_max]);
        return 0;
    }
    else return index_max;
}