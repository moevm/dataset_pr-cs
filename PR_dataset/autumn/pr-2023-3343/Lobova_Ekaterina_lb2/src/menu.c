#include <stdio.h>
#include "index_last_zero.h"
#include "index_first_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main()
{
    int action;
    scanf("%i",&action);
    int array[100];
    int len_array=0;
    while (getchar()!='\n'){
        scanf("%i",&array[len_array]);
        len_array++;
    }
    switch(action){
    case 0:
        printf("%i\n", index_first_zero(array,len_array));
        break;
    case 1:
        printf("%i\n", index_last_zero(array,len_array));
        break;
    case 2:
        printf("%li\n", sum_between(array,len_array));
        break;
    case 3:
        printf("%li\n", sum_before_and_after(array,len_array));
        break;
    default:
        printf("Данные некорректны");
    }
    return 0;
}
