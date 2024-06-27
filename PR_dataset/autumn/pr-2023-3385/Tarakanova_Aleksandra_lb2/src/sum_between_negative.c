
#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int a[],int l){
        int s=0;
        int j=index_first_negative(a, l);
        int k=index_last_negative(a, l);
        int i=j;
        for(i;i<k;i++){
                s+=abs(a[i]);
        }
        return s;
}
