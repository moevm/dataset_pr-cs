#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_ARR_LEN 100
int abs_max(int *array_nums, int len_arr){
    int max_num = 0;
    int ind_max = 0;
    for (int i = 1; i<len_arr; i++){
        if (abs(array_nums[i])>max_num){
            max_num = abs(array_nums[i]);
            ind_max = i;
        }
    }
    return ind_max;
}
int abs_min(int *array_nums, int len_arr){
    int min_num = INT_MAX;
    int ind_min = 0;
    for (int i = 1; i<len_arr; i++){
        if (abs(array_nums[i])<min_num){
            min_num = abs(array_nums[i]);
            ind_min = i;
        }
    }
    return ind_min;
    
}
int diff(int *array_nums, int ind_max, int ind_min){
   return array_nums[ind_max]-array_nums[ind_min];
    
}
int sum(int *array_nums, int len_arr, int ind_max){
    int sum = 0;
    for (int i = ind_max; i<len_arr;i++){
        sum+=array_nums[i];
    }
    return sum;
}
void data_input(int* array_nums, int* len_arr){
    while(scanf("%d", array_nums)==1){
        array_nums++;
        *len_arr+=1;
    }
}
void data_output(int* array_nums, int len_arr){
    switch (array_nums[0])
    {
    case 0:
        printf("%d\n", array_nums[abs_max(array_nums, len_arr)]);
        break;
    case 1:
        printf("%d\n", array_nums[abs_min(array_nums, len_arr)]);
        break;
    case 2:
        printf("%d\n", diff(array_nums, abs_max(array_nums,len_arr), abs_min(array_nums, len_arr)));
        break;
    case 3:
        printf("%d\n", sum(array_nums, len_arr, abs_max(array_nums,len_arr)));
        break;
    
    default:
        printf("Данные некорректны\n");
    }
}
int main()
{
    int len_arr = 0;
    int array_nums[MAX_ARR_LEN];
    data_input(array_nums, &len_arr);
    data_output(array_nums, len_arr);
    return 0;
}
