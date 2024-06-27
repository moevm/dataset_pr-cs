#include "index_last_negative.h"

int index_last_negative(int s[],int l){
        for(int i = l - 1; i >= 0; i--){
                if(s[i] < 0){
                        return i;
                }
        }
}
