#include "input_data.h"

int input_data(int nums[]){
    int size = 0, num;
    char space = ' '; 
    while (size < MAX_ARRAY_SIZE && space == ' '){
        scanf("%d%c", &num, &space);
	nums[size] = num;
        size++;
   }
   return size;
}
