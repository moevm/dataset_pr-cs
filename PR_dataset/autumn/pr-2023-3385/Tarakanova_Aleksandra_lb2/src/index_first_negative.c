#include "index_first_negative.h"
int  index_first_negative(int a[],int l){
        int n=0;
	int i=0;
        for(i;i<l;i++){
           if(a[i]<0){
              n=i;
              break;
           }
        }
        return  n;
}
