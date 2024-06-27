#include <stdio.h>
#include "sum_before_and_after_negative.h"

unsigned int sum_before_and_after_negative(int arr[], int size) {
  int first = index_first_negative(arr);
  int last = index_last_negative(arr, size);
  unsigned int sum = 0;

  for (int i = 0; i < size; i++) {
    if ((i < first) || (i >= last)) {
      sum += abs(arr[i]);
    }
  }
  return sum;
}
