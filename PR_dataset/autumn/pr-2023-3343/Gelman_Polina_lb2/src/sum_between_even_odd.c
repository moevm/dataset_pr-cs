#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int arr[], int size_arr){

int sum = 0;
  int first = index_first_even(arr,size_arr);
  int last = index_last_odd(arr,size_arr);
  for (int i=first;i<last;i++)
  {
  	sum += abs(arr[i]);

  }
    return sum;

}
