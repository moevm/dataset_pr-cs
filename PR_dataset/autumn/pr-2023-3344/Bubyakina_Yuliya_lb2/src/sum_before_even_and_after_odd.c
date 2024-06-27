#include "sum_before_even_and_after_odd.h"
int sum_before_even_and_after_odd(int array[],int number_of_numbers){
    int first_even=index_first_even(array,number_of_numbers),last_odd=index_last_odd(array,number_of_numbers);
    int summ=0;
    for(int i=0;i<first_even;i++){
        summ=summ+abs(array[i]);
    }
    for(int i=last_odd;i<number_of_numbers;i++){
        summ=summ+abs(array[i]);
    }
    return summ;
}
