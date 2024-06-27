#include "index_last_zero.h"
//код для поиска последнего вхождения нулевого элемента
int index_last_zero(int arr[], int size){
  for(int i=size-1; i>=0; i--){
    if(arr[i]==0){
      return i;
    }
  }
  return -1;
}
