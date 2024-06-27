#include "min.h"
#define N 100


int min(int arr[N], int chm);

int sum (int arr[N], int chm){
    int su=0;
    int m;
    int i =0;
    m=min(arr,chm);
    while(arr[i]!=m){
        su=su+arr[i];
        i=i+1;
    }
    return su;
}
