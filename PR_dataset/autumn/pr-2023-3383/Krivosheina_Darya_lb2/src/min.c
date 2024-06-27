#include <stdio.h>
#include "min.h"

int min(int massif2[], int len2){
        int minim = 100000;
        for (int i = 0; i < len2; i++){
                if (massif2[i] < minim){
                        minim = massif2[i];
                }
        }
        return minim;
}
