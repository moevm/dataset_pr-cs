#include <stdio.h>
#include "sum_between_negative.h"

unsigned int sum_between_negative(int arr[], int size) {
  int firstIndex = index_first_negative(arr);
  int lastIndex = index_last_negative(arr, size);
  unsigned int sum = 0;

  for (int i = firstIndex; i < lastIndex; i++) {
    sum += abs(arr[i]);
  }

  return sum;
}
