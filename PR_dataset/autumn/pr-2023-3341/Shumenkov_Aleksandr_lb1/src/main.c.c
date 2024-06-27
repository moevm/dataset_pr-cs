#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int arr[]);
int index_last_negative(int arr[], int size);
unsigned int sum_between_negative(int arr[], int size);
unsigned int sum_before_and_after_negative(int arr[], int size);

int main() {
  int a;
  scanf("%d", &a);
  int j = 0;
  int size = 0; 
  int arr[100];
  int x;
  char c = ' ';
  while(c !='\n'){
    scanf("%d%c", &arr[size], &c); 
    size++;
  };

  switch (a) {
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
  };
  return 0;
}

int index_first_negative(int arr[]) {
  int i = 0;
  while (arr[i] > 0) {
    i++;
  }
  return i;
}

int index_last_negative(int arr[], int size) {
  for (int j = size; j >= 0; --j) {
    if (arr[j] < 0) {
      return j;
    }
  }
  return -1;
}

unsigned int sum_between_negative(int arr[], int size) {
  int firstIndex = index_first_negative(arr);
  int lastIndex = index_last_negative(arr, size);
  unsigned int sum = 0;

  for (int i = firstIndex; i < lastIndex; i++) {
    sum += abs(arr[i]);
  }

  return sum;
}

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
