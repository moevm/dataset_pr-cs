#include <stdio.h>
#include <stdlib.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"


int main(){

int arr[100];
int j = 0,k,len;
char ch;
scanf("%d%c ",&k,&ch);

do{
 scanf("%d%c",&arr[j],&ch);
 j = j + 1;
}while(ch!='\n');
len = j;

switch(k){
 case 0:
   printf("%d",max(arr,len));
   break;
 case 1:
   printf("%d",min(arr,len));
   break;
 case 2:
   printf("%d",diff(arr,len));
   break;
 case 3:
   printf("%d ",sum(arr,len));
   break;
 default:
   printf("%s ","Данные некорректны");
}

return 0;
} 
