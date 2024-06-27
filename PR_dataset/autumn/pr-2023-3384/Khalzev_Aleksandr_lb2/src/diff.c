#include <stdio.h>
#include "diff.h"

int diff(int* s, int k) {

    int mx, mn;
    mx = max_i(s, k);
    mn = min_i(s, k);
    return mx - mn;
}
