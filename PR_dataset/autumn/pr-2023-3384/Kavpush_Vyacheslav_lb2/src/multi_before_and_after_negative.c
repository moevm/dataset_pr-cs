#include "multi_before_and_after_negative.h"
int multi_before_and_after_negative(int mas[], int len) {
        int f = index_first_negative(mas, len);
        int l = index_last_negative(mas, len);
        int proi = 1;
        for (int i=0; i<f; i++){
                proi *= mas[i];
        }
        for (int i=l; i<len+1; i++){
                proi *= mas[i];
        }
        return(proi);
}
