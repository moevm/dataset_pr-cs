#include "index_first_negative.h"
#include "index_last_negative.h"
int multi_between_negative(int a[], int count)
{
    int first = index_first_negative(a, count);
    int last = index_last_negative(a, count);
    int start=1;
    for(int i=first; i<last; i++)
    {
        start*=a[i];
    }
    return start;
}