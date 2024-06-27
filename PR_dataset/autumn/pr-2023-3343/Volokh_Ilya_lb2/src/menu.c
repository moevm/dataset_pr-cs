#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#define MAX_SIZE 100
int main(){
    int arr[MAX_SIZE];
    int size_now = 0;
    int to_do = 0;
    int first = -1;
    int last = -1;
    scanf("%d", &to_do);
    int symbol;
    while(size_now < MAX_SIZE && (scanf("%d", &arr[size_now]) == 1)){
        size_now++;
    }
    switch(to_do){
        case 0:
            printf("%d", index_first_zero(arr, size_now));
            break;
        case 1:
            printf("%d", index_last_zero(arr, size_now));
            break;
        case 2:
            printf("%d", sum_between(arr, size_now));
            break;
        case 3:
            printf("%d", sum_before_and_after(arr, size_now));
            break;
        default:
            printf("Данные некорректны");
    }
    return 0;
}

