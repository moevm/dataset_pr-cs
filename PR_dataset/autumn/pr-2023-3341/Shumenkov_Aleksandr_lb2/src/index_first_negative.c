#include "index_first_negative.h"

int index_first_negative(int arr[]) {
  int i = 0;
  while (arr[i] > 0) {
    i++;
  }
  return i;
}
