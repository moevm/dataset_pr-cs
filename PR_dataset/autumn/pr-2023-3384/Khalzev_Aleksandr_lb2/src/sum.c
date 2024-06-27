#include <stdio.h>
#include "sum.h"

int sum_mn(int s[], int k){
    int mn = 10000, sum = 0, suml = 0;
    for(int i = 0; i < k; i++){
        if(s[i] < mn){
            mn = s[i];
            sum = sum + suml;
            suml = 0;
        }
        suml = suml + s[i];
    }
    return sum;
}
