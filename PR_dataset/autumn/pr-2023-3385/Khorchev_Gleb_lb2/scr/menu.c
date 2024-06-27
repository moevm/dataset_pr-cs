#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
void main()
{
  int n;
  int i =0;
  int len = 0;
  int arr[100];
  
  scanf("%d", &n);
  
  do{
    scanf("%d", &arr[i]);
    i++;
    len++;
  }
  while(getchar() != '\n');
  switch(n){
      case 0:
          printf("%d\n", index_first_even(arr, len));
          break;
      case 1:
          printf("%d\n", index_last_odd(arr, len));
          break;
      case 2:
          printf("%d\n", sum_between_even_odd(arr, len));
          break;
      case 3:
          printf("%d\n", sum_before_even_and_after_odd(arr, len));
          break;
      default:
          printf("Данные некорректны\n");
  }

}
