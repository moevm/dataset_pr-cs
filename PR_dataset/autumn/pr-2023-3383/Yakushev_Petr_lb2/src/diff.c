#include "max.h"
#include "min.h"
#define N 100


int diff (int arr[N],int chm){
    int di=0;
    int ma,m;
    ma=max(arr);
    m=min(arr,chm);
    di=ma-m;
    return di;
}
