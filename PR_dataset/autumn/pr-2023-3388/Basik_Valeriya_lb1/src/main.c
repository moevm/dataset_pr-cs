#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int arr[], int array_size){
  int index = 0;
  for (int x = 1; x < array_size; x++){
    if(arr[x] < 0){
      return index;
      break;
    }
    index++;
  }
  index = -1;
  return index;
}

int index_last_negative(int arr[], int array_size){
  int index = array_size - 2;
  for (int x = array_size - 1; x >= 1; x--){
    if(arr[x] < 0){
      return index;
      break;
    }
    index--;
  }
  index = -1;
  return index;
}

int sum_between_negative(int arr[], int array_size){
  int first_negative = index_first_negative(arr, array_size);
  int last_negative = index_last_negative(arr , array_size);
  int result_sum = 0;
  for (int x = first_negative + 1; x < last_negative + 1; x++){
    result_sum += abs(arr[x]);
  }
  return result_sum;
}

int sum_before_and_after_negative(int arr[], int array_size){
  int first_negative = index_first_negative(arr, array_size);
  int last_negative = index_last_negative(arr, array_size);
  int result_sum = 0;
  for (int x = 1; x < first_negative + 1;x++){
    result_sum += abs(arr[x]);
  }
  for (int x = last_negative + 1; x < array_size; x++){
    result_sum += abs(arr[x]);
  }
  return result_sum;
}

void findIndexFirstNegative(int arr[], int count){
  int result = index_first_negative(arr, count);
  printf("%d\n", result);
}

void findIndexLastNegative(int arr[], int count){
  int result = index_last_negative(arr, count);
  printf("%d\n", result);
}

void findSumBetweenNegative(int arr[], int count){
  int result = sum_between_negative(arr, count);
  printf("%d\n", result);
}

void findSumBeforeAndAfterNegative(int arr[], int count){
  int result = sum_before_and_after_negative(arr, count);
  printf("%d\n", result);
}

int main(){
  int arr[101];
  int count = 0;
  do{
    if (count < 101){
      scanf("%d", &arr[count++]);
    }
  }while(getchar() != '\n');
  
  switch(arr[0]){
    case 0:
      findIndexFirstNegative(arr, count);
      break;
    case 1:
      findIndexLastNegative(arr, count);
      break;
    case 2:
      findSumBetweenNegative(arr, count);
      break;
    case 3:
      findSumBeforeAndAfterNegative(arr, count);
      break;
    default:
      printf("Данные некорректны");
  }
  
  return 0;
}
