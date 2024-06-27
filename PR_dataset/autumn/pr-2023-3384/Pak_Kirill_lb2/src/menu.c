#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main(){
    int arr[100];
    int ell;
    char sim;
    int len=0;
    char err[]="Данные некорректны";
    int prov=0;
    int fun;
    int first_zero;
    int last_zero;
    scanf("%d",&fun);
    for(int i=0;i<100;i++){
        if(scanf("%d%c",&ell,&sim)!=2){
            puts(err);
            return 0;
        }    
        arr[i]=ell;
        len+=1;
        if(sim=='\n'){
            break;
        }
    }
    for(int i=0;i<len;i++){
        if(arr[i]==0){
            prov=1;
            break;
        }
    }
    if(prov==0){
        puts(err);
        return 0;
    }
    first_zero=index_first_zero(arr,len);
    last_zero=index_last_zero(arr,len);
    switch(fun){
        case(0):
            printf("%d\n",first_zero);
            break;
        case(1):
            printf("%d\n",last_zero);
            break;
        case(2):
            printf("%d\n",sum_between(arr,first_zero,last_zero));
            break;
        case(3):
            printf("%d\n",sum_before_and_after(arr,first_zero,last_zero,len));
            break;
        default:
            puts(err);
            break;
        
    }
}