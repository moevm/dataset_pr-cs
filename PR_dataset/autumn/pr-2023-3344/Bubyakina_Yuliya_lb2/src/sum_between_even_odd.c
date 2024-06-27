#include "sum_between_even_odd.h"

int sum_between_even_odd(int array[],int number_of_numbers){
    int first_even=index_first_even(array,number_of_numbers),last_odd=index_last_odd(array,number_of_numbers);
    int summ=0;
    for(int i=first_even;i<last_odd;i++){
        summ=summ+abs(array[i]);
    }
    return summ;
}
