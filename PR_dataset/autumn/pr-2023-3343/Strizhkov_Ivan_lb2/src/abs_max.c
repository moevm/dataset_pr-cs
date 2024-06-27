#include <stdlib.h>
int abs_max(int arr[], int arr_size){
        int max = 0;

        for (int i = 0; i < arr_size; i++) {
                if (abs(arr[i]) > abs(max)){
                        max = arr[i];
                }
        }
        return max;
}