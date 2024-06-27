#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int array[], int length){
    int begin, finish, element, i, sum = 0;
    begin = index_first_even(array, length);
    finish = index_last_odd(array, length);
    for(i = begin; i < finish; i++){
        element = array[i];
        if(element < 0){element = -element;}
        sum += element;
    }
    return sum;
}