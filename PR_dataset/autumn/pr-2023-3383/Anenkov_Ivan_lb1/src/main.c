#include <stdio.h>
#include <stdlib.h>

#define maxN 100
int CNT_ARR = 0;

int index_first_zero(int arr[]);
int index_last_zero(int arr[]);
int sum_between(int arr[], int arrsum[]);
int sum_before_and_after(int arr[], int arrsum[]);



int main(){
    int task_key;
    int arr[maxN], arrsum[maxN];
    int num = 0, abs_sum = 0, zero =0;
    char enter;
    
    scanf("%d", &task_key);
    
    while (num < maxN && enter != '\n'){
        scanf("%d%c", &arr[num], &enter);
        abs_sum = abs_sum + abs(arr[num]);
        arrsum[num] = abs_sum;
        if (arr[num] == 0) zero += 1;
        num++;
    }    
     if (zero ==0){puts("Данные некорректны"); return 0; }
     
     CNT_ARR = num;
     
  switch(task_key){
    case 0:
        printf("%d\n", index_first_zero(arr));
        break;
    case 1:
        printf("%d\n", index_last_zero(arr));
        break;
    case 2 :
        printf("%d\n", sum_between(arr, arrsum));
        break;
    case 3 :
        printf("%d\n", sum_before_and_after(arr, arrsum));
        break;
    default:    
        puts("Данные некорректны");
   } 
   return 0;
}
    
    int index_first_zero(int arr[]){
        int ind_first = 0;
        for (int i = 0; i < CNT_ARR; i++){
            if (arr[i] == 0) {
                ind_first = i;
                break;
            }
        }
        return ind_first;
    }
    int index_last_zero(int arr[]){
        int ind_last = 0;
        for (int i = CNT_ARR-1; i >= 0; i--){
            if (arr[i] == 0) {
                ind_last = i;
                break;
            }
        }
        return ind_last;
    }
    int sum_between(int arr[], int arrsum[]){
        int res = arrsum[index_last_zero(arr)] - arrsum[index_first_zero(arr)];
        return res;
    }
    int sum_before_and_after(int arr[], int arrsum[]){
        int res = arrsum[CNT_ARR-1] - (arrsum[index_last_zero(arr)] - arrsum[index_first_zero(arr)]);
        return res;
    
    }
    



