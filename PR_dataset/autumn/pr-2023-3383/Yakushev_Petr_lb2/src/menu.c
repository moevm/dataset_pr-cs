#include <stdio.h>
#include <stdlib.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"
#define N 100





int main(){
    int chek,otv,chm,arr[N];
    scanf ("%d",&chek);
    chm=0;
    if (chek>3 || chek<0){
        printf("Данные некорректны\n");
        exit(0);
    }
    for (int i=0;i<N;i++){
        arr[i]=0;
    }
    for (int g = 0;g< N;g++) {
        scanf("%d", &arr[g]);
        chm++;
        if (arr[g]>100){
            printf("Данные некорректны\n");
            exit(0);
        }
        if (getchar()=='\n'){
            break;
        }
    }
    if (chek==0){
        otv =max(arr);
        printf("%d\n",otv);
    }
    if (chek==1){
        otv = min(arr,chm);
        printf("%d\n",otv);
    }
    if (chek==2){
        otv =diff(arr,chm);
        printf("%d\n",otv);
    }
    if (chek==3){
        otv =sum(arr,chm);
        printf("%d\n",otv);
    }
    
    return 0;
}
