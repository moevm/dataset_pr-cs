#include "multi_between_negative.h"
#include "index_last_negative.h"
#include "index_first_negative.h"
int multi_between_negative(int array[], int len){
    int a=index_first_negative(array, len);
    int b=index_last_negative(array, len);
    int k=1;
    for (int i=a; i<b; i++){
        k*=array[i];
    }
    return k;
}