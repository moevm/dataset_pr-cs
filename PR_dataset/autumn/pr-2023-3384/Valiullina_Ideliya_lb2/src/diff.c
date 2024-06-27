#include "diff.h"

int diff(int a[], int n){
    return abs_max(a,n) - abs_min(a,n);
}
