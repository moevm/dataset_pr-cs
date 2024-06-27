#include "sum_between.h"

int sum_beetwen(int M[],int frst,int end){
    int sum = 0;
    for(int i = frst;i < end;i++){
        sum += abs(M[i]);
        }
    return sum;
}
