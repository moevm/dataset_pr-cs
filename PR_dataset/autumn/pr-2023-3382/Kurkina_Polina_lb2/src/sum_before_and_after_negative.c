#include <stdio.h> 
#include <stdlib.h> 
#include "index_last_negative.h"
#include "index_first_negative.h"
int sum_before_and_after_negative(int Mas[100], int len){
    int ans = 0;
    int indexFirst = index_first_negative(Mas);
    if (indexFirst != -1){
        int indexSec = index_last_negative(Mas, len);
        int i = 0;
        while (i<indexFirst){
            ans += abs(Mas[i]);
            i++;
        }
        i = indexSec;
        while (i<len){     
            ans += abs(Mas[i]);
            i++;
        }
    }
    else{
        ans = -1;
    }
    return ans;
}
