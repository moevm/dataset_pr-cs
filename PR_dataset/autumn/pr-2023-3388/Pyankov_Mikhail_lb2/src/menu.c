#define MAX_INPUT_SIZE 20
#include "input_array_data.h"
#include "input_key_data.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "input_data_checking.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#include "switch_function.h"

int main()
{
    int key;
    input_key_data(&key);
    int length = 0;
    int array[MAX_INPUT_SIZE];
    input_array_data(array, &length);
    if(input_data_checking(array, key, length))
    switch_function(key, array, length);
    return 0;
}
