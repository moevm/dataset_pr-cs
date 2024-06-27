#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#define NUM_OF_ELEMS 1000

int compar(const void* a, const void* b)
{
    int num_one=*((int*)a);
    int num_two=*((int*)b);
    return abs(num_two)-abs(num_one);
}

int* input_arr(){
  int* arr = (int*)malloc(sizeof(int)*NUM_OF_ELEMS);
  for(int i=0; i<NUM_OF_ELEMS;i++)
    scanf("%d", &(arr[i]));
  return arr;
}

void output_arr(int* arr,clock_t start_time, clock_t end_time ){
  for(int i=0;i<NUM_OF_ELEMS;i++)
      printf("%d ", arr[i]);
  printf("\n%ld", (end_time-start_time));
}

int main()
{
    int* arr;
    arr=input_arr();
    clock_t start_time = clock();
    qsort(arr, NUM_OF_ELEMS, sizeof(int), compar);
    clock_t end_time = clock();
    output_arr(arr,start_time,end_time);
    free(arr);
    return 0;
}
