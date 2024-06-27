#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_before_and_after_negative(int arr[],int len){
    int multi=1;
    int f=index_first_negative(arr, len);
    int s=index_last_negative(arr,len);
    for (int i = 0; i < f; i++)
    {
        multi*=arr[i];
    }
    for (int i = s; i < len; i++)
    {
        multi*=arr[i];
    }
    return multi;
    
    
}
