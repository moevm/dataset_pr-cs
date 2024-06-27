#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int arr[], int ans, int i)
{
    ans=0;
    for (i = index_first_even(arr, ans, i); i < index_last_odd(arr, ans, i); i++)
    {
        ans=ans+abs(arr[i]);
    }

    return ans;
}
