#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void* a, const void* b){
    return (*(int*)a) >= (*(int*)b);
}

void bubbleSort(int array[], int size){
  int temp;
  for(int i = 0; i < size - 1; i++){
    for(int j = 0; j < size - i - 1; j++){
      if(array[j] > array[j+1]){
        temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
      }
    }
  }
}

int main(){
    int array[1000];
    for (int i = 0; i < 1000; i++) {
    scanf("%d", &array[i]);
  }
clock_t start_buble = clock();
bubbleSort(array, 1000);
clock_t end_buble = clock();
qsort(array, 1000, sizeof(int), compare);
clock_t end_qsrt = clock();
  for (int i = 0; i < 1000; i++) {
    printf("%d ", array[i]);
  }
printf("\n%f\n%f", (float)(end_buble-start_buble) / CLOCKS_PER_SEC, (float)(end_qsrt-end_buble) / CLOCKS_PER_SEC);
return 0;
}
