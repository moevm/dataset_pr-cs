#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"
#define N 100

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
            printf("%d\n", index_first_negative(arr, size));
            break;
         case 1:
             printf("%d\n", index_last_negative(arr, size));
             break;
         case 2:
            printf("%d\n", sum_between_negative(arr, size));
            break;
         case 3:
             printf("%d\n", sum_before_and_after_negative(arr, size));
             break;
         default:
             printf("%s\n", "Данные некорректны");
             break;
         }
   
}
