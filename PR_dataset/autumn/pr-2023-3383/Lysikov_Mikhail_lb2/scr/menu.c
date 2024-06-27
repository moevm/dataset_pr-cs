#include <stdio.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
int main(){
    int arr[100],size = 0, flag =1, option;
    char space;
    scanf("%d%c", &option, &space);
    while (flag){
        scanf("%d%c", &arr[size], &space);
        size++;
        if (space != ' ' ){
            flag = 0;
        }
    }
    switch (option) {
     case 0: printf("%d\n", abs_max(arr, size));break;
     case 1: printf("%d\n", abs_min(arr, size));break;
     case 2: printf("%d\n", diff(arr, size));break;
     case 3: printf("%d\n", sum(arr, size));break;
     default: printf("Данные некорректны\n");
 }
 return 0;
}
