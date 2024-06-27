#include "max.h"
#include <stdio.h>

int max_i(int s[], int k){
    int mx = 0;
    for(int i = 0; i < k; i++){
        if(s[i] > mx){
            mx = s[i];
        }
    }
    return mx;
}
