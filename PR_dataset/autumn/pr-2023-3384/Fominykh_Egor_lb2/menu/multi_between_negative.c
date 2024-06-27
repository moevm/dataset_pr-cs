#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int s[],int len)
{
    int p=1;
    int a = index_first_negative(s,len);
    int b = index_last_negative(s,len);
    for (int i=a;i<b;i++)
{
    p = p*s[i];
}
    return p;
}
