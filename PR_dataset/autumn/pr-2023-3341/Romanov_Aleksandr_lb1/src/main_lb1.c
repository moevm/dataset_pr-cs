#include <stdio.h>
#define N 100
#define spc ' '
#define flags "%d\n"
#include <stdlib.h>


//вынес ввод и вывод в отдельные функции

//ввел константу flags с флагами "%d\n" для printf

//убрал переменные с цифрами в названиях


int index_first_even (int arr[], int len){
    int res = 0;
    for (int i=0; i<len; i++){
        if ((abs(arr[i]))%2==0){
            res = i;
            return res;
        }
    }
}

int index_last_odd (int arr[],int len){
    int res = 0;
    for (int i=0; i<len; i++){
        if ((abs(arr[i]))%2==1){
            res = i;
        }

    }
    return res;
}

int sum_between_even_odd (int arr[], int len){
    int sum = 0;
    
    for (int i=index_first_even(arr, len); i<index_last_odd(arr, len); i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_even_and_after_odd (int arr[],int len){
    int sum = 0;
    
    for (int i=0; i<index_first_even(arr, len); i++){
        sum += abs(arr[i]);
    }
    for (int j=index_last_odd(arr, len); j<len; j++){
        sum += abs(arr[j]);
    }
    return sum;
}

int output(int value, int count, int *arr) {  
    switch(value){

        case 0:
        	printf(flags,index_first_even(arr, count));
        	break;
        case 1:
        	printf(flags,index_last_odd(arr, count));
        	break;
        case 2:
        	printf(flags,sum_between_even_odd(arr, count));
        	break;
        case 3:
        	printf(flags,sum_before_even_and_after_odd(arr, count));
        	break;
        default:
        	puts("Данные некорректны");
        	break;
    }
}

int input_value(){
    int value;
    scanf("%d", &value);
    return(value);
}

int input_arr(int arr[]){
    int count=0;
    char space = ' ';
    while (count<N && space == spc){
        scanf("%d%c", &arr[count],&space);
        count++;
    }
    return count;
}

int main(){
    int value = input_value();
    int arr[N];
    int count = input_arr(arr);
    output(value,count,arr);
}

