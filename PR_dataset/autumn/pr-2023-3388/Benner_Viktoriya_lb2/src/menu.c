#include <stdio.h>
#include <stdlib.h>
#include "input_type.h"
#include "input_array.h"
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "switch_function.h"
#define ARRAY_LENDTH 100
#define ERROR_MESSAGE "Данные некорректны"
int main(){
    int size = 0;
    char symbol;
    int arr[ARRAY_LENDTH];
    int type;
    input_type(type);
    input_array(symbol, size, arr);
    switch_funktion(type, arr, size);
    return 0;
}