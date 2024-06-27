#include <stdio.h>
#define ARR_MAX_SIZE 20

int index_first_negative(int arr[], int num_of_arr_elements){
    int res = 0;
    for(int i =0; i < num_of_arr_elements; i++){
        if(arr[i] < 0){
            res = i;
            break;
        }
    }
    return res;
}

int index_last_negative(int arr[], int num_of_arr_elements){
    int last_index = num_of_arr_elements - 1;
    int res = 0;
    for(int i = last_index; i>=0; i--){
        if(arr[i] < 0){
            res = i;
            break;
        }
    }
    return res;
}

int multi_between_negative(int arr[], int num_of_arr_elements){
    int last_neg = index_last_negative(arr, num_of_arr_elements);
    int first_neg = index_first_negative(arr, num_of_arr_elements);
    int res = 1;
    for(int i = first_neg; i<last_neg; i++){
        res = res*arr[i];
    }
    return res;
}

int multi_before_and_after_negative(int arr[], int num_of_arr_elements){
    int first_neg = index_first_negative(arr, num_of_arr_elements);
    int last_neg = index_last_negative(arr, num_of_arr_elements);
    int res = 1;
    for(int i = 0; i<first_neg; i++){
        res=res*arr[i];
    }
    for(int i = last_neg; i <num_of_arr_elements; i++){
        res=res*arr[i];
    }
    return res;
}

int console_input_opt(){
    int opt=0;
    scanf("%d", &opt);
    return opt;
}

int console_input_arr(int arr[]){
    int length = 0;
    char space = ' ';
    while(length < ARR_MAX_SIZE && space == ' '){
    	scanf("%d%c", &arr[length], &space);
    	length++;
    }
    return length;
}

int final_result(int case_num, int arr1[], int length){
    switch(case_num){
        case 0:
            printf("%d\n", index_first_negative(arr1, length));
            break;

        case 1:
            printf("%d\n", index_last_negative(arr1, length));
            break;

        case 2:
            printf("%d\n", multi_between_negative(arr1, length));
            break;

        case 3:
            printf("%d\n", multi_before_and_after_negative(arr1, length));
            break;

        default:
            printf("Данные некорректны");
            break;
    }
    return 0;
}

int main(){
    int option = console_input_opt();
    int arrayy[ARR_MAX_SIZE];
    int number_of_array_elements = console_input_arr(arrayy);
    final_result(option, arrayy, number_of_array_elements);
    return 0;
}
