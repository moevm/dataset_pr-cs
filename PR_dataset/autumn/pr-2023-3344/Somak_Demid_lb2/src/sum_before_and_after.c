#include "sum_before_and_after.h"

int sum_before_after(int M[],int frst,int frst2,int end ){
    int sum = 0;
    for(int i = 0;i < frst;i++){
        sum += abs(M[i]);
        }
    for(int i = frst2;i < end;i++){
        sum += abs(M[i]);
        }
    return sum;
}
