#include "abs_max.h"
#include <stdlib.h>
#include <stdio.h>
int sum(int arr_len, int arr[]){
        int mx = abs_max(arr_len, arr);
        int s = 0;
	int f = 0;
        for(int i = 0; i < arr_len; i++){
                if (f) s += arr[i];
                else if (abs(arr[i]) == abs(mx)) { s += mx; f = 1;}
        }
        return s;
}
