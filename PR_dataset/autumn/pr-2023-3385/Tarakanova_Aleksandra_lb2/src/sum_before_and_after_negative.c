
#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_before_and_after_negative(int a[],int l){
        int s=0;
        int j=index_first_negative(a, l);
        int k=index_last_negative(a, l);
        int i=0;
        for (i;i<j;i++){
                s+=abs(a[i]);
        }
        int h=k;
        for(h;h<l;h++){
                s+=abs(a[h]);
        }
        return s;
}
