#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int s[],int l){
        int in_f_n = index_first_negative(s,l);
        int in_l_n = index_last_negative(s,l);
        int sum = 0;
        for(int i = 0; i < in_f_n; i++){
                sum += abs(s[i]);
        }
        for(int j = in_l_n; j < l; j++){
                sum += abs(s[j]);
        }
        return sum;
}
