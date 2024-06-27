#include "max.h"

int max(int n[], int s) {
    int m = n[0]; 

    int i;
    for(i = 0; i < s; i++) {
        if(n[i] > m) m = n[i];
    }

    return m;
}