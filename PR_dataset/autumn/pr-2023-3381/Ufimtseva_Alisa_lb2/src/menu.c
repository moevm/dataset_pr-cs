#include <stdio.h>
#include <stdlib.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

#define N 100
#define str "Данные некорректны\n"

int arr[N];

int main(){
    int znach;
    scanf("%d",&znach);
    int i = 0;
    while (i < N) {
        scanf("%d", &arr[i]);
        i++;
        if (getchar() == '\n') {
            break;
        }
    }
    switch(znach){
        case 0:
            if (index_first_negative(arr)!=-1){
                printf("%d\n",index_first_negative(arr));
            }
            else{
                printf(str);
            }
            break;
        case 1:
            if (index_last_negative(arr)!=-1){
                printf("%d\n",index_last_negative(arr));
            }
            else{
                printf(str);
            }
            break;
        case 2:
            if (sum_between_negative()!=-1){
                printf("%d\n",sum_between_negative(arr));
            }
            else{
                printf(str);
            }
            break;
        case 3:
            if (sum_before_and_after_negative()!=-1){
                printf("%d\n",sum_before_and_after_negative(arr));
            }
            else{
                printf(str);
            }
            break;
        default:
            printf(str);
            break;
    }
}