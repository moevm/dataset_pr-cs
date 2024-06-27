#include "sum_between.h"
//код для нахождения суммы модулей элементов между нулевыми
int sum_between(int arr[], int size){
  int first=index_first_zero(arr, size);
  int last=index_last_zero(arr, size);
  int sum=0;
  for(int i=first+1; i<last; i++){
    sum+=abs(arr[i]);
  }
  return sum;
}
