#include "index_first_negative.h"

int index_first_negative(int s[],int l){
        for(int i = 0; i < l; i++){
                if(s[i] < 0){
                        return i+1;
                }
        }
}
