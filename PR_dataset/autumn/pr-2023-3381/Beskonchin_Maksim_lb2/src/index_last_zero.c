#include "index_last_zero.h"
int index_last_zero(int len_a ,int a[]){
    int index = -1;
    for (int index_for = 0; index_for < len_a; index_for++){
        if (a[index_for] == 0)
            index = index_for;
    }
    return index;
}