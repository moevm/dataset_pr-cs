#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
int main(){
    int n = 0, N = 100;
    int task, arr[N];
    scanf("%d", &task);
    char c;
    do{
        scanf("%d%c", &arr[n], &c);
        n++;
    } while (n < N && c != '\n');
    int len = n;
    switch (task){
    case 0:
        printf("%d\n", abs_max(arr, len));
        break;
    case 1:
        printf("%d\n", abs_min(arr, len));
        break;
    case 2:
        printf("%d\n", diff(arr, len));
        break;
    case 3:
        printf("%d\n", sum(arr, len));
        break;
    default:
        puts("Данные некорректны\n");
    }
    return 0;
}

