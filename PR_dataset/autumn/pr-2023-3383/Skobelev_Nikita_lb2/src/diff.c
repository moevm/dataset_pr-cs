#include <stdio.h>
#include "diff.h"
#include "max.h"
#include "min.h"
typedef int ll;
void diff(ll array[], ll cnt, ll task){
    printf("%d\n", array[max(array,cnt,task)]-array[min(array,cnt,task)]);
}