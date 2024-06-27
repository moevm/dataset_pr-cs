#include <stdio.h> 
int index_first_negative(int Mas[100]){
    int ans = -1;
    int i = 0;
    while (i<100){
        if (Mas[i]>= 0){
            i++;
        }else{
            ans = i;
            break;
        }
    }
    return ans;
}