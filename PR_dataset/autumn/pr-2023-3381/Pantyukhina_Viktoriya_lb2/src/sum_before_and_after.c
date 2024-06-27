#include "sum_before_and_after.h"
//сумма модулей элементов перед и после
int sum_before_and_after(int arr[], int size){
  int first=index_first_zero(arr, size);
  int last=index_last_zero(arr, size);
  int sum=0;
  for(int i=0; i<first; i++){
    sum+=abs(arr[i]);
  }
  for(int i=last+1; i<size; i++){
    sum+=abs(arr[i]);
  } 
  return sum;
}
