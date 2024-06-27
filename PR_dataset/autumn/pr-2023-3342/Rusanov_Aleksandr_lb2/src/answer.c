#include "answer.h"
#define OUTPUT "%d\n"

void answer(){
    int arr[N];
    int flag;
    int size = 0;
    flag = fill_arr(arr, &size);
    
    switch(flag){
        case 0:
            printf(OUTPUT, abs_max(arr, size, 1));
            break;
        case 1:
            printf(OUTPUT, abs_min(arr, size));
            break;
        case 2:
            printf(OUTPUT, diff(arr, size));
            break;
        case 3: ;
            int index = abs_max(arr, size, 2);
            printf(OUTPUT, sum(arr, size, index));
            break;
        default:
            printf("Данные некорректны");
    }
}
