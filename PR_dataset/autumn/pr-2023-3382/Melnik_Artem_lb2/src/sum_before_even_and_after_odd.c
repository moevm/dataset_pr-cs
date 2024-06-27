#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int arr[], int ans, int i)
{
    ans=0;
    
    for (i = 0; i < index_first_even(arr, i, ans); i++)
    {
        ans=ans+abs(arr[i]);
    }
    
    for (i = index_last_odd(arr, i, ans); i < 100; i++)
    {
        ans=ans+abs(arr[i]);
    }
    
    return ans;
}
