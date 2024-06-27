#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#include "abs_max.h"
#include "abs_min.h"
#include"diff.h"
int diff(int a[], int len_a){
        return (a[abs_max(a, len_a)] - a[abs_min(a, len_a)]);
}