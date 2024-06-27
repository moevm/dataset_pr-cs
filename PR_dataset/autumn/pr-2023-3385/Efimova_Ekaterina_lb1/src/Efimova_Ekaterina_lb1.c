#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define N 100
int get_index_first_negative(int arr[], int size)
{   int i;
    for (i = 0; i < size; i++)
    if (arr[i] < 0)
        return i;
        
}
int get_index_last_negative(int arr[], int size)
{   int i;
    for (i = size-1; i >= 0; i--)
    if (arr[i] < 0)
        return i;

}

int sum_between_negative(int arr[], int size)
{    int index_first_negative = get_index_first_negative(arr, size);
     int index_last_negative = get_index_last_negative(arr, size);
     int sum_between = 0;
     int i;
     for (i = index_first_negative; i < index_last_negative; i++){
        sum_between += abs(arr[i]);
     }
     return sum_between;  
}
       
int sum_before_and_after_between_negative(int arr[], int size)
{
    int sum_between_negative_for_3 = sum_between_negative(arr, size);
    int sum_after,total_sum = 0;
    int i;
    for (i = 0; i < size; i++){
        total_sum += abs(arr[i]);
    }
      sum_after = total_sum - sum_between_negative_for_3;
      return sum_after;
}

int main(){
    setlocale(LC_ALL, "Rus");
    int a;
    int arr[N], i;
    int size = 0;
    char tmp;
    scanf("%d", &a);
    for (i = 0; i < N; i++)
    { scanf("%d%c", &arr[i], &tmp);
      size+=1;
      if(tmp == '\n')
        break;
         
    }
    switch(a){
         case 0:
            printf("%d\n", get_index_first_negative(arr, size));
            break;
         case 1:
             printf("%d\n", get_index_last_negative(arr, size));
             break;
         case 2:
            printf("%d\n", sum_between_negative(arr, size));
            break;
         case 3:
             printf("%d\n", sum_before_and_after_between_negative(arr, size));
             break;
         default:
             printf("%s\n", "Данные некорректны");
             break;
         }
}

