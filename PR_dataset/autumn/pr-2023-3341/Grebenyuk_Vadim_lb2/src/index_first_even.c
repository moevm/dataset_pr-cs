#include "index_first_even.h"

#include "global.h"

int index_first_even() {
    for (int i = 0; i < length; i++)
        if ((nums[i] & 1) == 0)
            return i;
}