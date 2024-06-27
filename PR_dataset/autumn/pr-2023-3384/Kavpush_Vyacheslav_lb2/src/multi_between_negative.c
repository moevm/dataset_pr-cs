#include "multi_between_negative.h"
int multi_between_negative(int mas[], int len) {
    int f = index_first_negative(mas, len);
    int l = index_last_negative(mas, len);
    int proi = 1;
    for (int i=f; i<l; i++){
        proi *= mas[i];
    }
    return(proi);
}