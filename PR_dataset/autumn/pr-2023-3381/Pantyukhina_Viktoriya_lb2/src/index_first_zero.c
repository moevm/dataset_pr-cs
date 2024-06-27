#include "index_first_zero.h"
//код для поиска первого  вхождения нулевого элемента в массив
int index_first_zero(int arr[], int size){
  for(int i=0; i<size; i++){
    if(arr[i]==0){
      return i;
    }
  }
  return -1; //в случае ошибки
}

