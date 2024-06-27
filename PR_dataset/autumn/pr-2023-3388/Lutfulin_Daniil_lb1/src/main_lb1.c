#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int index_first_negative(int[], int);
int index_last_negative(int[], int);
int sum_between_negative(int[], int);
int sum_before_and_after_negative(int[], int);
void get_numbers(int*, int*, int**);
void print_answer(int, int*, int);

int index_first_negative(int arr[], int arr_len){
    int index = -1;
    for (int i = 0; i < arr_len; i++) {
        if (arr[i] < 0) {
            index = i;
            break;
        }
    }
    return index;
}

int index_last_negative(int arr[], int arr_len) {
    int index = -1;
    for (int i = arr_len; i >0; i--) {
        if (arr[i] < 0) {
            index = i;
            break;
        }
    }
    return index;
}

int sum_between_negative(int arr[], int arr_len) {
    int first = index_first_negative(arr, arr_len), last = index_last_negative(arr,arr_len);
    int summary = -1;
    if (first != -1){
        summary++;
    	for (int i = first; i < last; i++) {
    	    summary += abs(arr[i]);
   	}}
    return summary;
}


int sum_before_and_after_negative(int arr[], int arr_len) {
    int first = index_first_negative(arr, arr_len), last = index_last_negative(arr,arr_len);
    int summary = -1;
    if (first != -1){
    summary++;
    for (int i = 0; i < first; i++) {
        summary += abs(arr[i]);
    }
    for (int i = last; i < arr_len; i++) {
        summary += abs(arr[i]);
    }}
    return summary;
}

void get_numbers(int *real_len, int *case_num, int **arr){
    int arr_len=0;
    int first_number;
    scanf("%d", case_num);
    *arr = malloc(MAX_SIZE * sizeof(int));
    do {
      scanf("%d", &(*arr)[arr_len]);
      arr_len++;
    } while (getchar() != '\n');
    *real_len = arr_len;
    
}


void print_answer(int case_num, int *arr, int arr_len){
    switch(case_num){
        case 0:
                printf("%d\n", index_first_negative(arr, arr_len));
                break;
            case 1 :
                printf("%d\n", index_last_negative(arr, arr_len));
                break;
            case 2:
                printf("%d\n", sum_between_negative(arr, arr_len));
                break;
            case 3:
                printf("%d\n", sum_before_and_after_negative(arr, arr_len));
                break;
            default:
                printf("Данные некорректны\n");
                break;
    }
}

int main(){
    int case_num, arr_len;
    int *arr;
    get_numbers(&arr_len, &case_num, &arr);
    print_answer(case_num, arr, arr_len);
    free(arr);
    return 0;
}
