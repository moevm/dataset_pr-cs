#include "input_array.h"
int input_array(int array[]){
    int length = 0;
    int j = 0;
    while(1){
        scanf("%d", &array[j]);
        j++;
        length++;
        if (getchar()=='\n'){
            break;
        }

    }
    return length;
}