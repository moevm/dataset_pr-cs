#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 100
int abs_max(int array[], int len);
int abs_min(int array[], int len);
int diff(int array[], int len, int ind_max, int ind_min);
int sum(int array[], int len, int ind_max);
    int main(){
    int ind_max, ind_min;
    int array[N];
    int num_oper;
    char space;
    int k = 0;
    scanf("%d%c", &num_oper, &space);
    do{
        scanf("%d%c", &array[k], &space);
        k ++;
    }while(space != '\n');
    int len = k;
    switch(num_oper){
        case 0:
            printf("%d\n", array[abs_max(array,len)]);
            break;
        case 1:
            printf("%d\n", array[abs_min(array, len)]);
            break;
        case 2:
            ind_max = abs_max(array, len);
            ind_min = abs_min(array, len);
            printf("%d\n", diff(array, len, ind_max, ind_min));
            break;
        case 3:
            ind_max = abs_max(array, len);
            printf("%d\n", sum(array, len, ind_max));
            break;
        default:
            printf("Данные некорректны\n");
}
}
int abs_max(int array[], int len){
    int max = 0;
    int ind_max;
    for (int i = 0; i < len; i++){
        if (abs(array[i]) > max){
            max = abs(array[i]);
            ind_max = i;
        }
    }
    return ind_max;
}
int abs_min(int array[], int len){
    int min = abs(INT_MAX);
    int ind_min;
    for (int i = 0; i < len; i++){
        if (abs(array[i]) < min){
            min = abs(array[i]);
            ind_min = i;
        }
    }
    return ind_min;
}
int diff(int array[], int len, int ind_max, int ind_min){
    return array[ind_max] - array[ind_min];
}
int sum(int array[], int len, int ind_max){
    int sum_after_max = 0;
    for (int i = ind_max; i < len; i++){
        sum_after_max += array[i];
    }
    return sum_after_max;
}

