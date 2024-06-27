#include <stdio.h>
#include <stdlib.h>
int index_first_even(int arr[], int ans, int i)
{
    for (i = 0; i < 100; i++)
    {
        if((arr[i])%2==0)
        {
            ans=i;
            return ans;
            break;
        }
    }
}

int index_last_odd(int arr[], int ans, int i)
{
    for (i = 0; i < 100; i++)
    {
        if(arr[i]%2!=0)
        {
            ans=i;
        }
    }
    return ans;
}

int sum_between_even_odd(int arr[], int ans, int i)
{
    int first_even=index_first_even(arr, ans, i);
    int last_odd=index_last_odd(arr, ans, i);
    ans=0;
    for (i = first_even; i < last_odd; i++)
    {
        ans=ans+abs(arr[i]);
    }
    
    return ans;
}

int sum_before_even_and_after_odd(int arr[], int ans, int i)
{
    int first_even=index_first_even(arr, i, ans);
    int last_odd=index_last_odd(arr, i, ans);
    ans=0;
    
    for (i = 0; i < first_even; i++)
    {
        ans=ans+abs(arr[i]);
    }
    
    for (i = last_odd; i < 100; i++)
    {
        ans=ans+abs(arr[i]);
    }
    
    return ans;
}

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
      
