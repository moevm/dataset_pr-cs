#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
int main(void){
    int arr[100]={0};
    int count = -1;
    int option_number;
    int number;
    do{
        scanf("%d",&number);
        if (count==-1){
            option_number = number;
            count++;
        }
        else{
            arr[count] = number;
            count++;
        }
    }while (getchar()!='\n');
    switch (option_number){
        case 0:
            printf("%d\n",index_first_negative_func(arr, count));
            break;
        case 1:
            printf("%d\n",index_last_negative_func(arr, count));
            break;
        case 2:
            printf("%d\n",sum_between_negative_func(arr, count));
            break;
        case 3:
            printf("%d\n",sum_before_and_after_negative_func(arr, count));
            break;
        default:
            printf("Данные некорректны\n");
    }
    
    return 0;
}
