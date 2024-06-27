#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int array[], int size_array){ // Сумма модулей элементов массива, расположенных от первого чётного элемента и до последнего нечётного, включая первый и не включая последний
    int sum = 0; 
    int start = index_first_even(array, size_array); 
    int end = index_last_odd(array, size_array);
    if (start < end){
        for(int i = start; i < end; i++)
            sum += abs(array[i]);
    } else{
        for(int i = end + 1; i <= start; i++)
            sum += abs(array[i]);
    }
    return sum;
}
