#include <stdio.h> 
int index_last_negative(int Mas[100], int len){
    int ans = -1;
    int i = 0;
    for(i; i<len; i++){
        if (Mas[i]< 0){
            ans = i;
        }
    }
    return ans;
}
