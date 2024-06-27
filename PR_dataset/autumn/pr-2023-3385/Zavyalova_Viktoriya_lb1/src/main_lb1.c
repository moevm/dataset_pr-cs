#include <stdio.h>

int max(int arr[],int len){
 int ma=arr[0];
   for(int i=0;i<len;i++){
     if(arr[i]>ma){
 ma=arr[i];
 }
 }
 return ma;

}

int min (int arr[],int len){
 int mi = arr[0];
 for(int i=0;i<len;i++) {
   if (arr[i] < mi) 
     mi = arr[i];
}

return mi;
}

int diff(int arr[],int len){
    int mx,mn;
    mx =max(arr,len);
    mn=min(arr,len);
    return mx-mn;
}

int sum(int arr[],int len){
    int b=0,z=min(arr,len);
    for(int i=0;arr[i]!=z;i++){
        b=b+arr[i];
    }
    return b;
}

int main(){

int arr[100];
int j=0,k,len;
char ch;
scanf("%d%c ",&k,&ch);

do{
 scanf("%d%c",&arr[j],&ch);
 j=j+1;
}while(ch!='\n');
len=j;

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
