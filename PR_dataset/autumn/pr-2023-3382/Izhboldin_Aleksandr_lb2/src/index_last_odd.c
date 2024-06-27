#include "index_last_odd.h"

int index_last_odd(int last_id, long long array[]){
    for (int i = last_id; i >= 0 ; i--)
        if (array[i]%2 != 0)
            return i;
}
