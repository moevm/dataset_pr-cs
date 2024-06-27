#include <stdlib.h>
int abs_min(int arr[], int arr_size){
        int min = arr[0];
        for (int i = 0; i < arr_size; i++){
                if (abs(arr[i]) < abs(min)){
                        min = arr[i];
                }
        }
        return min;
}