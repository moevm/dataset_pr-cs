#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after.h"
#include "index_last_zero.h"
#include "index_first_zero.h"

int sum_before_and_after(int mas[], int len){
        int cnt = 0, il = 0;
        int ifz = index_first_zero(mas, len);
        int ilz = index_last_zero(mas, len);
        for(; il < ifz; il++){
                cnt += abs(mas[il]);
        }
        for(--len;len> ilz; --len){
                cnt += abs(mas[len]);
        }
        return cnt;
}
