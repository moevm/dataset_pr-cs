#include "index_last_zero.h"
#include "index_first_zero.h"

long sum_between(int a[], int n){
    int i_first=index_first_zero(a,n);
    int i_last=index_last_zero(a,n);
    long sum=0;
    for (int i=i_first;i<=i_last;i++){
        sum+=abs(a[i]);
    }
    return sum;
}
