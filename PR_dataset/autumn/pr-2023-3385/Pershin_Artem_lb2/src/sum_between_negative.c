#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_between_negative(int s[],int l){
        int in_f_n = index_first_negative(s,l);
        int in_l_n = index_last_negative(s,l);
        int sum = 0;
        for(int i = in_f_n; i < in_l_n; i++){
                sum += abs(s[i]);
        }
        return sum;
}
