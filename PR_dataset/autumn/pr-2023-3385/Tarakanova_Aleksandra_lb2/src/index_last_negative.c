#include"index_last_negative.h"
int index_last_negative(int a[],int l){
        int n=0;
        int i=l-1;
        for(i;i>=0;i--){
           if(a[i]<0){
           n=i;
           break;
           }
        }
        return n;
}
