#include "abs_max.h"

int abs_max(int a[], int n){
    int a_max_ans, a_abs_max = 0;
    for(int i = 0; i < n; i++){
        if(abs(a[i]) > a_abs_max){
            a_abs_max = abs(a[i]);
            a_max_ans = a[i];
        }
    }
    return a_max_ans;
}