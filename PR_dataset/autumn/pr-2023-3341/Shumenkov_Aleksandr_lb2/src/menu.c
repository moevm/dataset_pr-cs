#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

void input_option(int* option);
void input(int* size, int arr[]);
void cases(int option, int size, int arr[]);

int main() {
  int option;
  input_option(&option);
  int size = 0; 
  int arr[100];
  input(&size, arr);
  cases(option,size, arr);
 return 0;
}

void input_option(int* option){
	scanf("%d", option);
}

void input(int* size, int arr[]){
  char symvol = 0;	
  while( symvol != '\n'){
    scanf("%d%c", &arr[*size], &symvol);
    (*size)++;
  }
}

void cases(int option, int size, int arr[]){ 
  switch(option) {
  case 0:
    printf("%d\n", index_first_negative(arr));
    break;

  case 1:
    printf("%d\n", index_last_negative(arr,size));
    break;

  case 2:
    printf("%d\n", sum_between_negative(arr, size));
    break;

  case 3:
    printf("%d\n", sum_before_and_after_negative(arr,size));
    break;

  default:
    printf("Данные некорректны\n");
  }
 
}

