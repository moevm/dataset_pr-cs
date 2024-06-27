#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_before_and_after_negative(int a[], int count)
{
    int first = index_first_negative(a, count);
    int last = index_last_negative(a, count);
    int start=1;
    for(int i=0; i<first; i++)
    {
        start*=a[i];
    }
    for(int i=last; i<count; i++)
    {
        start*=a[i];
    }
    return start;
}