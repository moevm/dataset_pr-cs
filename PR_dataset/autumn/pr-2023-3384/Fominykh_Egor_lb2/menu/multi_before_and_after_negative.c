#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#include "index_last_negative.h"
#include "index_first_negative.h"

int multi_before_and_after_negative(int s[],int len)
{
    int doo = 1;
    int pos = 1;
    int a = index_first_negative(s,len);
    int b = index_last_negative(s,len);
    for(int i=0;i<a;i++)
{
    doo = doo*s[i];
}
    for(int i=b;i<len;i++)
{
    pos = pos*s[i];
}
    return doo * pos;
}