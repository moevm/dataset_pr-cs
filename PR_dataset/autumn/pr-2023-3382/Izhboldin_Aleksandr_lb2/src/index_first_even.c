#include "index_first_even.h"

int index_first_even(int last_id, long long array[]){
    for (int i = 0; i <= last_id; i++)
        if (array[i]%2 == 0)
            return i;
}
