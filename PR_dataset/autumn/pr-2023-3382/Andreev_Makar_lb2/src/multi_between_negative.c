#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_between_negative(int arr[],int len){
    int multi=1;
    int f=index_first_negative(arr, len);
    int s=index_last_negative(arr,len);
    for (int i = f; i < s; i++)
    {
        multi*=arr[i];
    }
    return multi;
    

}
