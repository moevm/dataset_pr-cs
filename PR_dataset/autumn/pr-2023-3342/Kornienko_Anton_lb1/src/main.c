#include <stdio.h>
#include <stdlib.h>


#define N 100



int index_first_even(int array[],int size);
int index_last_odd(int array[], int size);
int sum_between_even_odd(int array[], int index1, int index2);
int sum_before_even_and_after_odd(int array[], int index1, int index2, int size);
int input_in_array(int array[],int* Ptrlen);
void processing(int num, int array[],int len);

int main()
{   
    
    int arr[N];
    int len = 0;
    int* ptr_len = &len;
    int command_number = input_in_array(arr, ptr_len);
    processing(command_number, arr,len);


    return 0;
}

int input_in_array(int array[],int* ptr_len){
    int command;
    char space = ' ';
    scanf("%d", &command);
    while (*ptr_len < N && space == ' ') {
        scanf("%d%c", &array[*ptr_len], &space);
        *ptr_len = *ptr_len + 1;
        }
    return command;
}



void processing(int num, int array[],int len){

    int index_first = index_first_even(array,len);
    int index_last = index_last_odd(array,len);


    switch(num){
        case 0:
            printf("%d\n", index_first);
            break;
        case 1:
            printf("%d\n", index_last);
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(array,index_first,index_last));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(array,index_first,index_last,len));
            break;
        default:
            printf("Данные некорректны");
    }
}

int index_first_even(int array[],int size){
    int result = - 1;
    for(int i = 0; i < size; ++i){
        if(abs(array[i]) % 2 == 0){
            result = i;
            break;
        }
    }
    return result;
}

int index_last_odd(int array[], int size){
    int result = -1;

    for(int i = 0; i < size; ++i){
        if(abs(array[i]) % 2 == 1){
            result = i;
        }
    }
    return result;
}

int sum_between_even_odd(int array[], int index_even, int index_odd){
    int sum = 0;
    for(int i =  index_even; i < index_odd; ++i){
        sum += abs(array[i]);
    }
    return sum;
}
int sum_before_even_and_after_odd(int array[], int index_even, int index_odd, int size){
    int sum = 0;
    for(int i = 0 ; i < index_even; ++i){
        sum += abs(array[i]);
    }
    for(int i = index_odd; i < size;++i){
        sum += abs(array[i]);
    }
    return sum;
}
