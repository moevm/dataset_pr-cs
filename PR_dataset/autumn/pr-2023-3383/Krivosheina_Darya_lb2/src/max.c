#include <stdio.h>
#include "max.h"

int max(int massif1[], int len1){
        int maxim = 0;
        for (int i = 0; i < len1; i++){
                if (massif1[i] > maxim){
                        maxim = massif1[i];
                }
        }
        return maxim;
}
