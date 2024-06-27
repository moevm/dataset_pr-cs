#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 100
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main(){
    int ind_max, ind_min;
    int array[N];
    int num_oper;
    char space;
    int k = 0;
    scanf("%d%c", &num_oper, &space);
    do{
        scanf("%d%c", &array[k], &space);
        k ++;
    }while(space != '\n');
    int len = k;
    switch(num_oper){
        case 0:
            printf("%d\n", abs_max(array,len));
            break;
        case 1:
            printf("%d\n", abs_min(array, len));
            break;
        case 2:
            printf("%d\n", diff(array, len));
            break;
        case 3:
            printf("%d\n", sum(array, len));
            break;
        default:
            printf("Данные некорректны\n");
        }
	return 0;
}
