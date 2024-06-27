#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main()
{
    int func_num;
    int ans=0;
    int arr[100];
    int i=0;
    
    for (i = 0; i < 100; i++)
        arr[i]=0;
        
    scanf("%d", &func_num);
        
    for (i = 0; i < 100; i++)
        scanf("%d",&arr[i]);
        
    switch(func_num)
    {
        case 0: ans=index_first_even(arr,i,ans);
        break;
        case 1: ans=index_last_odd(arr,i,ans);
        break;
        case 2: ans=sum_between_even_odd(arr,i,ans);
        break;
        case 3: ans=sum_before_even_and_after_odd(arr,i,ans);
        break;
        default: puts("Данные некорректны");
        return 0;
    }
    printf("%d\n",ans);
    
    return 0;
}
