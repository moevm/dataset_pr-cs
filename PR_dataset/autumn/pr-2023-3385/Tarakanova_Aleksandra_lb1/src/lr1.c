#include <stdio.h>
#include <stdlib.h>
int  index_first_negative(int a[],int l){
        int n=0;
        for(int i=0;i<l;i++){
           if(a[i]<0){
              n=i;
              break;
           }
        }
        return  n;
}
int index_last_negative(int a[],int l){
        int n=0;
        for(int i=l-1;i>=0;i--){
           if(a[i]<0){
           n=i;
           break;
           }
        }
        return n;
}
int sum_between_negative(int a[], int l){
        int s=0;
        int j=index_first_negative(a, l);
        int k=index_last_negative(a, l);
        for(int i=j;i<k;i++){
                s+=abs(a[i]);
        }
        return s;
}
int sum_before_and_after_negative(int a[], int l){
        int s=0;
        int j=index_first_negative(a, l);
        int k=index_last_negative(a, l);
        for (int i=0;i<j;i++){
                s+=abs(a[i]);
        }
        for(int i=k;i<l;i++){
                s+=abs(a[i]);
        }
        return s;
}
int main(){
        int n;
        char m;
        scanf("%d%c",&n,&m);
        int a[100];
        int i=0;
        do{
                scanf("%d%c",&a[i],&m);
                i++;
        }while (m!='\n');
        int l=i;
        switch(n){
                case 0: printf("%d\n",index_first_negative(a, l));
                        break;
                case 1:
                        printf("%d\n",index_last_negative(a,l));
                        break;
                case 2:
                        printf("%d\n",sum_between_negative(a,l));
                        break;
                case 3: printf("%d\n",sum_before_and_after_negative(a,l));
                        break;
               default:
                        printf("Данные некорректны"); 
        }
        return 0;
}


