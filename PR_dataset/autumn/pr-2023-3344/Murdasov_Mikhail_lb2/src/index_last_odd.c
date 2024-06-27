#include <stdio.h>
#include <stdlib.h>
int index_last_odd(int array[], int ind_count){
    int i;
    int index_answer;
    int flag;
    for(i = 0; i<ind_count; i++){
        if(array[i] % 2 != 0){
            index_answer = i;
            flag = 1;
        }
    }

    if(flag != 1){
        puts("Данные некорректны\n");
        return 0;
    }

    return index_answer;
}