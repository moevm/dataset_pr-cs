#include <stdio.h>
#include "func.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"
#include "index_first_negative.h"
#define NEW_LINE_INTEGER_FORMAT "%d\n"

void func(){
    int answer = 0;
    
    int Num=100;
    int arr[Num];
    int number=0;
    char check;
    
    int key;
    scanf("%d%c", &key, &check);
    while(check!='\n' && number<Num){
        scanf("%d%c", &arr[number], &check);
        number++;
    }
    
    switch ( key){
        case 0:
            ptintf(NEW_LINE_INTEGER_FORMAT,index_first_negative(arr, number));
            break;
        case 1:
            printf(NEW_LINE_INTEGER_FORMAT,index_last_negative(arr, number));
            break;
        case 2:
            printf(NEW_LINE_INTEGER_FORMAT,sum_between_negative(arr, number));
            break;
        case 3:
            printf(NEW_LINE_INTEGER_FORMAT,sum_before_and_after_negative(arr, number));
            break;
        default:
            prinf("Данные некорректны");
    }
}