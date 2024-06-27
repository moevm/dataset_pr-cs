#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main() {
    int subtask_number, fl = 1, length = 0;
    scanf("%d", &subtask_number);
    int array[100];
    char check;
    while(fl){
        scanf("%d%c", &array[length], &check);
        length ++;
        if(check == '\n'){fl = 0;}
    }
    if((length == 0) || (subtask_number < 0) || (subtask_number > 3)){
        printf("Данные некорректны");
    } else {
        int result;
        switch (subtask_number) {
            case 0:
                result = index_first_even(array, length);
                break;
            case 1:
                result = index_last_odd(array, length);
                break;
            case 2:
                result = sum_between_even_odd(array, length);
                break;
            case 3:
                result = sum_before_even_and_after_odd(array, length);
                break;
        }
        printf("%d\n", result);
    }
    return 0;
}