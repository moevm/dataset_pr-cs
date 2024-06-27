#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "input.h"
#include "output.h"
#define N 100

int main()
{   
    
    int arr[N];
    int len = 0;
    int* ptr_len = &len;
    int command_number = input(arr, ptr_len);
    output(command_number, arr,len);


    return 0;
}
