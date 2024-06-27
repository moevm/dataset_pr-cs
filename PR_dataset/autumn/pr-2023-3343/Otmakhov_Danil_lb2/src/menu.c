#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
int arr[20];

int main(){
    int counterSizeOfArr = 0;
    int command;
    int sizeOfArr;
    scanf("%d", &command);
    while (getchar() != '\n'){
        scanf("%d", &arr[counterSizeOfArr]);
        counterSizeOfArr++;
    }
    sizeOfArr = counterSizeOfArr;
    switch(command){
        case 0: printf("%d\n", index_first_negative(arr, sizeOfArr));
                break;
        case 1: printf("%d\n", index_last_negative(arr, sizeOfArr));
                break;
        case 2: printf("%d\n", multi_between_negative(arr, sizeOfArr));
                break;
        case 3: printf("%d\n", multi_before_and_after_negative(arr, sizeOfArr));
                break;
        default: printf("Данные некорректны\n");
    }
    return 0;
}
