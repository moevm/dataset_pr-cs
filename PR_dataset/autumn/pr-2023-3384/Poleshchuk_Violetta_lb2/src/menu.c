#include <stdio.h>
#include <stdlib.h>

#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"


int main(){
    int act;
    scanf("%d", &act);
    int arr[100] = {0};
    int index = 0;
    int num;
    do{
        if (scanf("%d", &num) == 1){
            arr[index] = num;
        }
        else{
            printf("Данные некорректны");
            return 0;
        }
        index++;
    } while(getchar()!= '\n' && index < 100);

    switch(act){
        case 0:
            printf("%d\n", index_first_negative(arr));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr));
            break;
        case 2:
            printf("%d\n", sum_between_negative(arr));
            break;
        case 3:
            printf("%d\n", sum_before_and_after_negative(arr));
            break;
        default:
            printf("Данные некорректны");
	}

    return 0;
}
