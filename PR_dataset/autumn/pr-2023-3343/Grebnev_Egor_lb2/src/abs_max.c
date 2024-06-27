#include <stdlib.h>
int abs_max(int arr_len, int arr[]){
        int mx = 0;

        for (int i = 0; i < arr_len; i++) {
                if (abs(arr[i]) > abs(mx)){
                        mx = arr[i];
                }
        }
        return mx;
}
