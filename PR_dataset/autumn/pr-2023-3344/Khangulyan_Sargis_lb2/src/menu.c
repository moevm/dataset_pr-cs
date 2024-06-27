#include <stdio.h>
#include “abs_max.h”
#include “abs_min.h”
#include “diff.h”
#include “sum.h”
int main(){
    int arr[100], r;
    int arrsize = 0;
    scanf("%d", &r);
    while(getchar() != '\n'){
        scanf("%d", &arr[arrsize]);
        arrsize++;
    }
    if ((arrsize > 100) || (arrsize <= 0)){
        printf("Данные некорректны\n");
        return 0;
    }
    else{
        switch(r){
            case 0:
                printf("%d\n", abs_max(arr, arrsize, 1));
                break;
            case 1:
                printf("%d\n", abs_min(arr, arrsize));
                break;
            case 2:
                printf("%d\n", diff(arr, arrsize));
                break;
            case 3:
                printf("%d\n", sum(arr, arrsize));
                break;
            default:
                printf("Данные некорректны\n");
                break;
        }
    }
    return 0;
}