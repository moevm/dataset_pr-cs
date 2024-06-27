//created by niks (student LETI)

#include <stdio.h>
#include "diff.h"
#include "sum.h"
#include "min.h"
#include "max.h"

typedef int ll;

int main(){
        ll array[100];
        ll task;
        scanf("%d",&task);
        ll cnt=0;
        for(ll i=0;i<100;++i){
            scanf("%d",&array[i]);
            cnt++;
            if(getchar()=='\n')break;
        }
        switch(task){
            case 0:
                max(array,cnt,task);
                break;
            case 1:
                min(array,cnt,task);
                break;
            case 2:
                diff(array,cnt,task);
                break;
            case 3:
                sum(array,cnt,task);
                break;
            default:
                printf("Данные некорректны\n");
        }
        return 0;
}