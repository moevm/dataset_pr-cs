#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_before_and_after_negative(int list[],int length){
    int firstneg = index_first_negative(list,length);
    int lastneg = index_last_negative(list,length);
    int pr = 1;
    for(int i=0;i<firstneg;i++){
        pr *= list[i];
    }
    for(int i = lastneg;i<length;i++){
        pr *= list[i];
    }
    return pr;
}

