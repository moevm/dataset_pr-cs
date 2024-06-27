#include "index_last_negative.h"

int index_last_negative(int s[],int len)
{
    for (int i=len-1;i>=0;i--)
{
    if (s[i]<0)
{
    return i;
}
}
}