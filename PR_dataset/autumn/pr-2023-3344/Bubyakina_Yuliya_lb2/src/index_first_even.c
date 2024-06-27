#include "index_first_even.h"
int index_first_even(int array[],int number_of_numbers){
    int first_even;
    for(int i=0;i<number_of_numbers;i++){
        if(array[i]%2==0){
            first_even = i;
            break;
        }
    }
    return first_even;
}
