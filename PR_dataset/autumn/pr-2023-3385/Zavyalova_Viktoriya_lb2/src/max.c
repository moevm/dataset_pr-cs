#include "max.h"

int max(int arr[],int len){
 int ma = arr[0];
   for(int i = 0;i < len;i++){
     if(arr[i] > ma){
 ma = arr[i];
 }
 }
 return ma;

}
 