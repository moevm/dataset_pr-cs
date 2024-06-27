#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"
#include "menu.h"
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


