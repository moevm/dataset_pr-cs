#include "abs_max.h"
int sum(int arr[], int size) {
 int sum = 0, flag = 0;
 int max = abs_max(arr, size);
 for (int i=0; i<size; i++) {
     if (flag && size < 101){
         sum+= arr[i-1];
     }
     if (arr[i]==max){
         flag = 1;
     }
 }sum = sum + arr[size-1];
 return sum;
}
