#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"

int main()
{
    int arr[100];
    int n=0; 
    int m, t;
    scanf("%d",&m);
    while( n < 100 ){
        char  space;
        int  r = scanf( "%d%c", &arr[n], &space );
         if( r==EOF )break; 
         n++;
         if( r==1 )break;  
         if( r==2 && space=='\n' )break;  
    }
    if(n==0){
        printf("Данные некорректны\n");
        return 0;
    }
    switch (m){
        case 0: t = arr[ abs_max(arr,n) ];
                printf("%d\n",t);
                break;
        case 1: t = arr[ abs_min(arr,n) ];
                printf("%d\n",t);
                break;
        case 2: t = diff(arr,n);
                printf("%d\n",t);
                break;
        case 3: t = sum(arr,n);
                printf("%d\n",t);
                break;
        default: printf("Данные некорректны\n");
                break;
    }
    
    return 0;
} 
