#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main(){
    int n = 0, N = 100;
    int type, arr[N];
    scanf("%d",&type);
    char c;
    do{
        scanf("%d%c", &arr[n], &c);
        n++;
    } while(c != '\n' && n < N);
    int len_arr = n;
    switch (type){
    case 0:
        printf("%d\n", abs_max(arr,len_arr));
        break;
    case 1:
        printf("%d\n", abs_min(arr,len_arr));
	    break;
    case 2:
        printf("%d\n", diff(arr,len_arr));
	    break;
    case 3:
        printf("%d\n",sum(arr,len_arr));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
    return 0;
}
