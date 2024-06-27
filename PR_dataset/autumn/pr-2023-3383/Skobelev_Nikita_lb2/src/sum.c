#include <stdio.h>
#include "sum.h"
#include "min.h"
typedef int ll;
void sum(ll array[], ll cnt, ll task){
    ll sum=0;
    for(ll i=0;i<min(array,cnt,task);++i)sum+=array[i];
    printf("%d\n",sum);
}