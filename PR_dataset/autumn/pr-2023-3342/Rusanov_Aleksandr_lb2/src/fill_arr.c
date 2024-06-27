#include "fill_arr.h"
int fill_arr(int arr[], int *size){
    int flag;
    *size = 0;
    scanf("%d", &flag);
    while(getchar() != '\n') {
        scanf("%d", &arr[(*size)++]);
    }
    return flag;
}
