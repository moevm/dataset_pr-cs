#include "index_first_negative.h"
int index_first_negative(int list[],int length){
    int index;
    for(int j = 0;j<length;j++){
        if(list[j]<0){
            index = j;
            break; 
     	}
    }
    return index;
}
