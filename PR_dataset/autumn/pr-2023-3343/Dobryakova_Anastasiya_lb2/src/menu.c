#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

#define MAX_LEN 100

int main(){

    //Ввод данных ...
    int key_value;
    scanf("%d", &key_value);

    int size = 0;
    int arr[MAX_LEN];
    while(getchar()!='\n'){
        scanf("%d", &arr[size]);
        size++;
    }
    //...

    switch(key_value){

        case 0:
            printf("%d\n", index_first_negative(arr, size));
            break;

        case 1:
            printf("%d\n", index_last_negative(arr, size));
            break;

        case 2:
            printf("%d\n", sum_between_negative(arr, size));
            break;

        case 3:
            printf("%d\n", sum_before_and_after_negative(arr, size));
            break;

        default:
            printf("Данные некорректны");
    }
    return 0;
}
