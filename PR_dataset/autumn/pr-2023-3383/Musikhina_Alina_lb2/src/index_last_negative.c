#include "index_last_negative.h"

int index_last_negative(int mas[], int ln){
    int indposl;
    for (int i=ln-1; i>=0; i--)
    {
        if (mas[i] < 0)
    {       indposl=i;
            break;
        }
        
    }
    return indposl;
}

