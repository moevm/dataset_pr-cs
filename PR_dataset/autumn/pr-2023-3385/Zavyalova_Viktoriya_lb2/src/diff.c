
#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int arr[],int len){
    int mx, mn;
    mx = max(arr,len);
    mn = min(arr,len);
    return mx - mn;
} 