#include "abs_min.h"

int abs_min(int a[], int n){
    int a_min_ans = a[0], a_abs_min = abs(a[0]);
    for(int i = 0; i < n; i++){
        if(abs(a[i]) < a_abs_min){
            a_abs_min = abs(a[i]);
            a_min_ans = a[i];
        }
    }
    return a_min_ans;
}
