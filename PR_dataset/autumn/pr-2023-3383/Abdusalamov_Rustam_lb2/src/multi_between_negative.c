#include "index_last_negative.h"
#include "index_first_negative.h"
int multi_between_negative(int list[],int length){
    int firstneg = index_first_negative(list,length);
    int lastneg = index_last_negative(list,length);
    int proizv = 1;
    while(firstneg < lastneg){
        proizv = proizv*list[firstneg];
        firstneg += 1;
    }
    return proizv;
}

