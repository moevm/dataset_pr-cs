#include "max.h"
#include "min.h"

int diff(int n[], int s) {
    return max(n, s) - min(n, s);
}