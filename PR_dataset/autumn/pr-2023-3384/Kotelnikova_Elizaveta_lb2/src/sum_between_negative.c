#include <stdio.h>
#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int i, int arr[100]){
    int j=index_first_negative(i, arr);
    int k=index_last_negative(i, arr);
    int s=0;
    for (j; j<k; ++j){
        s=s+abs(arr[j]);
    }
    printf("%d\n", s);
    return 0;
}