#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "abs_min.h"
#define N 100

int abs_min(int a[], int len_a){
        int abs_min = abs(INT_MAX), ind_amn;
        for (int i = 0; i < len_a; i++){
                if (abs(a[i]) < abs_min){
                        abs_min = abs(a[i]);
                        ind_amn = i;
                }
        }
        return ind_amn;
}