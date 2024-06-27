#include "abs_max.h"

int sum(int arr[], int count)
{
    int maxim = abs_max(arr, count);
    int flag = 0;
    int summa = 0;
    for(int i = 0; i < count; ++i){
        if(flag == 0){
            if(maxim == arr[i]){
                flag = 1;
                summa += arr[i];
            }
        } else {
            summa += arr[i];
        }
    }
    return summa;
}
