#include <stdlib.h>
int abs_min(int arr_len, int arr[]){
        int mn = arr[0];
        for (int i = 0; i < arr_len; i++){
                if (abs(arr[i]) < abs(mn)){
                        mn = arr[i];
                }
        }
        return mn;
}
