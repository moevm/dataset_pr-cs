#include <stdio.h> 
#include <stdlib.h> 
#include "index_last_negative.h"
#include "index_first_negative.h"
int sum_between_negative(int Mas[100], int len){
    int ans = 0;
    int indexFirst = index_first_negative(Mas);
    if (indexFirst!=-1){
        int indexSec = index_last_negative(Mas, len);
        int i = indexFirst;
        while (i<indexSec){
            ans += abs(Mas[i]);
            i++;
        }
        
    }
    else{
        ans = -1;
    }
    
    return ans;
}
