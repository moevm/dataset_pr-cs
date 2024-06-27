#include <stdio.h>
#include <stdlib.h>
#include "index_last_zero.h"
int index_last_zero(int quantity, int arr_end[100]){
    for (quantity; quantity >= 0; --quantity){
        if (arr_end[quantity] == 0){
            return quantity;
        }
    }
}