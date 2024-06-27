#include <stdio.h>
#include <stdlib.h>
#include "sum_between.h"
#include "index_last_zero.h"
#include "index_first_zero.h"

int sum_between(int mas[], int len){
        int cnt = 0;
        int ifz = index_first_zero(mas, len) + 1;
        int ilz = index_last_zero(mas, len);
        for(ifz; ifz < ilz; ++ifz){
                cnt += abs(mas[ifz]);
        }
        return cnt;
}

