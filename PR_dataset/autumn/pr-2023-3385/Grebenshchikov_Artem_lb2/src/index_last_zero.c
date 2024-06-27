#include "index_last_zero.h"

int index_last_zero(int mas[], int len){
        int g = len- 1;
        for(; g >= 0; --g){
                if (mas[g] == 0){
                        return g;
                }
        }
}
