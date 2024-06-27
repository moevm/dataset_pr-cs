#include "sum.h"
#include "abs_max.h"

int sum(int a[], int n){
    int flag = 0, sum = 0;

    for(int i = 0; i < n; i++){
        if(a[i] == abs_max(a,n)){
            flag = 1;
        }
        if(flag != 0){
            sum += a[i];
        }
    }
    return sum;
}
