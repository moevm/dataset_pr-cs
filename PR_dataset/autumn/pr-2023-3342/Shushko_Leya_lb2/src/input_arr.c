#include "input_arr.h"
void input_arr(int* arr,int* size,int* number){
    scanf("%d",number);
    while (getchar()!='\n') {
        scanf("%d",&arr[(*size)++]);
    }
}
