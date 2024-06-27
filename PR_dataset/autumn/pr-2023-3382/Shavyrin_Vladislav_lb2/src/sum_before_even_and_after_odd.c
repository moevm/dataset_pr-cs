#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h" 

int sum_before_even_and_after_odd(int array[], int size_array){ // Сумма модулей элементов массива, расположенных до первого чётного элемента (не включая элемент) и после последнего нечётного (включая элемент)
    int sum = 0; 
    int start = index_first_even(array, size_array); 
    int end = index_last_odd(array, size_array);
    for(int i = 0; i < start; i++)
        sum += abs(array[i]);
    for(int i = end; i < size_array; i++)
        sum += abs(array[i]);
    return sum;
}
