#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_before_and_after.h"
#include "sum_between.h"
#define N 100
int n;
int arr[N];
void menu(int n, int arr[], int size){
  switch(n){
  case 0:
  printf("%d\n", index_first_zero(arr, size));
  break;

  case 1:
  printf("%d\n", index_last_zero(arr, size));
  break;

  case 2:
  printf("%d\n", sum_between(arr, size));
  break;

  case 3:
  printf("%d\n", sum_before_and_after(arr, size));
  break;

  default:
  printf("Данные некорректны\n");
  break;
  }
}

int main(){
  scanf("%d", &n);
  int counter=0;
  while(counter<N){
    scanf("%d", &arr[counter]);
    counter++;
    if (getchar()=='\n'){
      break;
    }
  }
  menu(n, arr, counter);
  return 0;
}
