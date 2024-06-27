#include <stdio.h>
#include "input_array.h"
#include "answer.h"
#define MAX_SIZE 100
#define print_str "%d\n"

int main(){
        int array[MAX_SIZE];
        int znach;
        scanf("%d", &znach);
        int len;
        len = input_array(array);
        answer(znach, array,length);
        return 0;
}
