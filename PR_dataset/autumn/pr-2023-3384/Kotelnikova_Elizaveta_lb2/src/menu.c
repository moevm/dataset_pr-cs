#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
int main(){
    int N;
    scanf("%d", &N);
    if (N!=0 && N!=1 && N!=2 && N!=3){
        printf("Данные некорректны");
        return 0;
        }
    int i=0;
    char st=' ';
    int arr[100];
    while (i<100){
        scanf("%d%c", &arr[i], &st);
        i=i+1;
        if (st=='\n'){
            break;
            }
        }
    if (N==0){
        printf("%d\n", index_first_negative(i, arr));
        }
    else if (N==1){
        printf("%d\n",index_last_negative(i, arr));
        }
    else if (N==2){
        sum_between_negative(i, arr);
        }
    else if (N==3){
        sum_before_and_after_negative(i, arr);
        }
    return 0;
}