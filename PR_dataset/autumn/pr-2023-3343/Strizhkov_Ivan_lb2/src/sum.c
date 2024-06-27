#include "abs_max.h"
#include <stdlib.h>
#include <stdio.h>
int sum(int arr[], int arr_size){
        int max = abs_max(arr_size, arr);
        int sum = 0;
	int found = 0;
        for(int i = 0; i < arr_size; i++){
                if (found) sum += arr[i];
                else if (abs(arr[i]) == abs(max)) { sum += max; found = 1;}
        }
        return sum;
}