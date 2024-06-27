#include "index_last_odd.h"

#include "global.h"

int index_last_odd() {
    for (int i = length - 1; i > 0; i--)
        if (nums[i] & 1)
            return i;
}