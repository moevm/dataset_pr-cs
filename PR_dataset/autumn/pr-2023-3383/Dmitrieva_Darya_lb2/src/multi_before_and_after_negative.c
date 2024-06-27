#include "multi_before_and_after_negative.h"
#include "index_last_negative.h"
#include "index_first_negative.h"
int multi_before_and_after_negative(int array[], int len ){
    int a=index_first_negative(array, len);
    int b=index_last_negative(array, len);
    int a1=1;
    int b1=1;
    for (int i=0; i<a; i++){
        a1*=array[i];
    }
    for (int i=b;i<=len-1;i++){
        b1*=array[i];
    }
    return a1*b1;
}