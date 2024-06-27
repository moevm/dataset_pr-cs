#include "index_first_negative.h"

int index_first_negative(int mas[], int ln){
    int indperv;
    for (int i=0; i<ln; i++)
    {
        if (mas[i] < 0){
            indperv=i;
            break;
        }
    }
    return indperv;
}

