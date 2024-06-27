#include "index_first_zero.h"
int index_first_zero(int len_a ,int a[]){
    for (int index = 0; index < len_a; index++){
        if (a[index] == 0)
            return index;}
    return -1;
}
