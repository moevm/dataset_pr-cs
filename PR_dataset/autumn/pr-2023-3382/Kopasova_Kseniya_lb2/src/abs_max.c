#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "abs_max.h"


int abs_max(int a[], int len_a){
        int abs_max = 0, ind_amx;
        for (int i = 0; i < len_a; i++){
                if (abs(a[i]) > abs_max){
                        abs_max = abs(a[i]);
                        ind_amx=i;
                }
        }
        return ind_amx;
}