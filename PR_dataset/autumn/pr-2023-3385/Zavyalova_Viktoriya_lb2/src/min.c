#include "min.h"

int min (int arr[],int len){
 int mi = arr[0];
 for(int i = 0;i < len;i++) {
   if (arr[i] < mi) 
     mi = arr[i];
}

return mi;
}
 