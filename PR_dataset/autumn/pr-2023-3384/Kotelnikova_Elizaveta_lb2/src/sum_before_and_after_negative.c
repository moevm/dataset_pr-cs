#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_before_and_after_negative(int i, int arr[100]){
    int j=index_first_negative(i, arr);
    int k=index_last_negative(i, arr);
    int s1=0;
    int l=0;
    for (l; l<j; ++l){
        s1=s1+abs(arr[l]);
        }
    int l1=k; 
    for (l1; l1<i; ++l1){
        s1=s1+abs(arr[l1]);
        }
    printf("%d\n", s1);
    return 0;
}