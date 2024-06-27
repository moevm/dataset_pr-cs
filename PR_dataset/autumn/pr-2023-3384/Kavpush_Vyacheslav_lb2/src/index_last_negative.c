#include "index_last_negative.h"
int index_last_negative(int mas[], int len) {
        int otv = 0;
        for (int j=len; j>=0; j--){
                if (mas[j] < 0){
                        otv = j;
                        break;
                }
        }
        return (otv);
}