#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "output.h"
#define STR_OUT "%d\n"

void output(int num, int array[],int len){

    int index_first = index_first_even(array,len);
    int index_last = index_last_odd(array,len);


    switch(num){
        case 0:
            printf(STR_OUT, index_first);
            break;
        case 1:
            printf(STR_OUT, index_last);
            break;
        case 2:
            printf(STR_OUT, sum_between_even_odd(array,index_first,index_last));
            break;
        case 3:
            printf(STR_OUT, sum_before_even_and_after_odd(array,index_first,index_last,len));
            break;
        default:
            printf("Äàííûå íåêîððåêòíû");
    }
}
