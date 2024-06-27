#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 1000

int compare_numbers(const void *a, const void  *b);
void sort_with_time(int *arr, double *time);
void read_to_arr(int* arr);
void print_answer(int *arr, double *time);

int compare_numbers(const void *a, const void  *b){
    const int* first = (const int*)a;
    const int* second = (const int*)b;
    if (*first < *second)
        return 1;
    if (*first > *second)
        return -1;
    return 0;
}

void sort_with_time(int *arr, double *time){
  clock_t start_of_sort = clock();
  qsort(arr,SIZE,sizeof(int),compare_numbers);
  clock_t end_of_sort = clock();
  *time = (double)(start_of_sort-end_of_sort)/CLOCKS_PER_SEC;
}

void read_to_arr(int* arr){
    size_t len = 1000*SIZE;
    char *input = (char*)malloc(len*sizeof(char));
    fgets(input,len,stdin);
    char *token = strtok(input, " ");
    int num_index = 0;
    while(token){
        arr[num_index] = atoi(token);
        token = strtok(NULL, " ");
        num_index++;
    }
}

void print_answer(int *arr, double *time){
    for(int i = 0;i<SIZE-1;i++){
    printf("%d ",arr[i]);
  }
  printf("%d\n",arr[SIZE-1]);
  printf("%f",*time);
}

int main(){
  int* arr = (int*)malloc(SIZE*sizeof(int));
  read_to_arr(arr);

  double time_of_sort;
  sort_with_time(arr, &time_of_sort);
  print_answer(arr,&time_of_sort);

  return 0;
  }