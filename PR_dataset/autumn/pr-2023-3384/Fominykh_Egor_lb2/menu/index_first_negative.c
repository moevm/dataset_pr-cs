#include "index_first_negative.h"

int index_first_negative(int s[],int len)
{
    for (int i=0;i<len;i++)
{
    if (s[i]<0)
{
    return i;
}
}
}