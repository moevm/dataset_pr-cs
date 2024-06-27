#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "sum.h"
#include"abs_max.h"
#define N 100

int sum(int a[], int len_a){
        int s = 0;
        for (int i= abs_max(a, len_a); i < len_a; i++){
               s += a[i];
        }
        return s;
}