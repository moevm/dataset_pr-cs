#include <stdio.h>
#include"input_data.h"
#include"print_result.h"

#define MAX_ARR_SIZE 100



int main()
{
    int array[MAX_ARR_SIZE];
    int array_size = 0;
    int operation_number;

    input_data(array, &array_size, &operation_number);
    print_result(array, array_size, operation_number);
    return 0;
}


