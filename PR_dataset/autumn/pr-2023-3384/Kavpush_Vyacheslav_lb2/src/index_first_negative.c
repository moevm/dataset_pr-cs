#include "index_first_negative.h"
int index_first_negative(int mas[], int len) {
        int otv = 0;
        for (int j=0; j<len; j++){
                if (mas[j] < 0){
                        otv = j;
                        break;
                }
        }
        return (otv);
}