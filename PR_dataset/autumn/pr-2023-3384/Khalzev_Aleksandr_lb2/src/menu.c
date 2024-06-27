#include <stdio.h>
#include "max_i.h"
#include "min_i.h"
#include "diff.h"
#include "sum.h"

void main(){
    int n, l = 0, I[100];
    char d;
    scanf("%d", &n);
    while(1){
        scanf("%d%c", &I[l], &d);
        l = l + 1;
        if(d == '\n'){
            break;
        }
    }
    switch(n){
    case 0:
        printf("%d\n", max_i(I, l));
        break;
    case 1:
        printf("%d\n", min_i(I, l));
        break;
    case 2:
        printf("%d\n", max_i(I, l) - min_i(I, l));
        break;
    case 3:
        printf("%d\n", sum_mn(I, l));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
}
