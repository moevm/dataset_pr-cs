#include <stdio.h>
#include "sum_between.h"
#include "sum_before_and_after.h"

int main(){
    int a,arr[100],ch;
    scanf("%d",&a);
    int n = 0;
    for(int i = 0; ((ch = getchar()) != '\n'); i++){
            scanf("%d",&arr[i]);
            n++;
        }
    switch(a){
            case 0:
                printf("%d\n", first_zero(arr,n));
                break;
            case 1:
                printf("%d\n", last_zero(arr,n));
                break;
            case 2:
                printf("%d\n", sum_beetwen(arr,first_zero(arr,n),last_zero(arr,n)));
                break;
            case 3:
                printf("%d\n", sum_before_after(arr,first_zero(arr,n),last_zero(arr,n),n));
                break;
            default:
                puts("Данные некорректны");
    };
}
