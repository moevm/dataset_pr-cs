#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"

int main() {
    int array[100];
    char space;
    int key;
    int i = 0, array_lenght = 0;
    
    
    scanf("%d",&key);
    do{
        scanf("%d%c", &array[i], &space);
        i ++;
        array_lenght ++;
    } while(space != '\n');

    switch(key){
        case 0:
            printf("%d",index_first_negative(array,array_lenght));
            break;
        case 1:
            printf("%d",index_last_negative(array,array_lenght));
            break;
        case 2:
            printf("%d",sum_between_negative(array,array_lenght));
            break;
        case 3:
            printf("%d",sum_before_and_after_negative(array,array_lenght));
            break;
        default:
            printf("%s","Данные некорректны");
        }
    
    
}