#include <stdio.h>
#include <stdlib.h>

int abs_max(int arr[], int n){
    int max_val = abs( arr[0] );
    int max_index = 0;
    int k;
    for ( k=1; k<n; ++k ){
        if (max_val < abs(arr[ k ])){
            max_val = abs(arr[ k ]);
            max_index = k; 
        }
    } 
    return max_index;
}

int abs_min(int arr[], int n){
    int min_val = abs( arr[0] );
    int min_index = 0;
    int k;
    for ( k=1; k<n; ++k ){
        if (min_val > abs( arr[ k ])){
            min_val = abs( arr[ k ]); 
            min_index = k;
        }
    } 
    return min_index;
}

int diff(int arr[], int n){
    int min_index = abs_min( arr, n );
    int max_index = abs_max( arr, n );
    return arr[ max_index ] - arr[ min_index ];
}

int sum(int arr[], int n){
    int max_index = abs_max( arr, n );
    int j, suma = 0;
    for (j=max_index; j<n; ++j ){
        suma += arr[ j ];
    }
    return suma;
}

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
