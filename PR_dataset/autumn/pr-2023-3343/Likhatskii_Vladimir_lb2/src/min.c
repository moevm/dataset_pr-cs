#include "min.h"

int min(int n[], int s) {
    int m = n[0]; 

    int i = 0;
    for(i = 0; i < s; i++) {
        if(n[i] < m) m = n[i];
    }

    return m;
}