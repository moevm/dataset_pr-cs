#include <stdio.h>
#include "min.h"

int min_i(int s[], int k){
    int mn = 10000;
    for(int i = 0; i < k; i++){
        if(s[i] < mn){
            mn = s[i];
        }
    }
    return mn;
}
