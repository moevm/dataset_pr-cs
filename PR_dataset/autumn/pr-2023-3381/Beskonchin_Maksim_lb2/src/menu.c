#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#define str "Данные некорректны\n"

int main(){
    setlocale(LC_ALL, "Rus");
    int number;
    scanf("%d", &number);
    int array[100];
    int len_array = 0;

    while (len_array < 100) {
        int num;
        if (scanf("%d", &num) == 1) {
            array[len_array] = num;
            len_array++;
        } else {
            break;
        }
    }

    switch(number){
        case 0:
            if (index_first_zero(len_array, array) != -1){
            printf("%d\n", index_first_zero(len_array, array));
            }
            else{
                    printf(str);
            }
            break;
        case 1:
            if (index_last_zero(len_array, array) != -1){
                printf("%d\n", index_last_zero(len_array, array));
            }
            else{
                printf(str);
            }
            break;
        case 2:
            if (sum_between(len_array, array) != -1){
        printf("%d\n", sum_between(len_array, array));
    }
            else{
        printf(str);
    }
            break;
        case 3:
            if (sum_before_and_after(len_array, array) != -1){
                printf("%d\n", sum_before_and_after(len_array, array));
            }
            else{
                printf(str);
            }
            break;
        default:
            printf(str);;
            break;
    }
    return 0;
}