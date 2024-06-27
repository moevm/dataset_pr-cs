#include <stdio.h>
#include "min.h"
#include "max.h"
#include "diff.h"
int diff(int arr[], int n){
    return max(arr, n)-min(arr, n);
}
