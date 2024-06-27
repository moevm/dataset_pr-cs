#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int arr[], int size_arr){
int sum = 0;
  int first = index_first_even(arr,size_arr);
  int last = index_last_odd(arr,size_arr);
  for (int i = 0;i<first;i++)
  {
  	sum += abs(arr[i]); 
  }
  for (int i = last; i < size_arr;i++)
  {
	sum += abs(arr[i]);  
  
  }
  return sum;

}
