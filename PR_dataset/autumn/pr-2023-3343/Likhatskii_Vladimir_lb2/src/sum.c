#include "min.h"

int sum(int n[], int s) {
    int res = 0; 
    int m = min(n, s); 

    int i = 0; 
    while(n[i] != m) {
        res += n[i];
        i++;
    }

    return res;
}