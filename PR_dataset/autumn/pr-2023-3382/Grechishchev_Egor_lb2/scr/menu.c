#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "index_1.h"
#include "diff.h"
#include "sum.h"
#include "abs_min.h"

int main(){
    int arr[100];
    int a;
    char space;
    int size = 0;
    scanf( "%d%c", &a , &space );
    for( int i = 0 ; i < 100 ; i++ ){
        scanf( "%d%c", &arr[i] , &space );
        size++;
        if (space == '\n'){
            break;
        }
    }
    int b;
    switch(a){
        case 0:
            b = abs_max(arr, size);
            printf("%d\n", b);
            break;
        case 1:
            b = abs_min(arr, size);
            printf("%d\n", b);
            break;
        case 2:
            b = diff(arr, size);
            printf("%d\n", b);
            break;
        case 3:
            b = sum(arr, size);
            printf("%d\n", b);
            break;
        default:
        printf("Данные некорректны\n");
    }
    return 0;
}