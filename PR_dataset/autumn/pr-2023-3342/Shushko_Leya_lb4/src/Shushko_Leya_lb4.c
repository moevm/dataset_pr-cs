#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
#define IF_TRUE "exists\n"
#define IF_FALSE "doesn't exist\n"
#define VERIFIABLE_NUMBER 0
#define FLOAT_OUTPUT "%f\n"
#define INT_INPUT "%d"
void input(int* arr){
    for (int number =0; number<SIZE; number++){
        scanf(INT_INPUT, &arr[number]);
    }
}
int compar(const void* left_element, const void* right_element){
    const int* first_element = (const int*)left_element;
    const int* second_element = (const int*)right_element;
    if (*first_element<*second_element){
        return -1;
    }
    if (*first_element==*second_element){
        return 0;
    }
    if (*first_element>*second_element){
        return 1;
    }    
}
int check_zero_binary(int* arr, const int verifiable_number){
    time_t start_time=time(NULL);
    int* result=bsearch(&verifiable_number,arr,sizeof(arr)/sizeof(int*),sizeof(int), compar);
    time_t end_time = time(NULL);
    if (result){
        return 1;
    } else{
        return 0;
    }
    double seconds = difftime(end_time, start_time);
    double* pointer_seconds= &seconds;
}
int check_zero_manually(int* arr){
    for(int number = 0; number<SIZE;number++){
        if(arr[number]==0){
            return 1;
        }
    }
    return 0;
}
int time_for_check_zero_manually(int* arr){
    time_t start_time = time(NULL);
    check_zero_manually(arr);
    time_t end_time =time(NULL);
    return difftime(end_time,start_time);
}
void output(int* arr, const int verifiable_number){
    int result_of_binary= check_zero_binary(arr, verifiable_number);
    if (result_of_binary){
        printf(IF_TRUE);
    } else{
        printf(IF_FALSE);
    }
    double seconds_for_binary;
    double* pointer_seconds = &seconds_for_binary;
    printf(FLOAT_OUTPUT,seconds_for_binary);
    int result_of_manually = check_zero_manually(arr);
    if (result_of_manually){
        printf(IF_TRUE);
    } else {
        printf(IF_FALSE);
    }
   double seconds_for_manually= time_for_check_zero_manually(arr);
   printf(FLOAT_OUTPUT,seconds_for_manually);
}
int main(){
    int arr[SIZE];
    input(arr);
    qsort(arr,SIZE,sizeof(int),compar);
    const int verifiable_number = VERIFIABLE_NUMBER;
    output(arr,verifiable_number);
    return 0;
}
