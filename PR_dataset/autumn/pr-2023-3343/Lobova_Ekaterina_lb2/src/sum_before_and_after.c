#include "index_last_zero.h"
#include "index_first_zero.h"

long sum_before_and_after(int a[], int n){
    int i_first=index_first_zero(a,n);
    int i_last=index_last_zero(a,n);
    long sum=0;
    for (int i=0;i<i_first;i++){
        sum+=abs(a[i]);
    }
    for (int i=i_last+1;i<n;i++){
        sum+=abs(a[i]);
    }
    return sum;
}
