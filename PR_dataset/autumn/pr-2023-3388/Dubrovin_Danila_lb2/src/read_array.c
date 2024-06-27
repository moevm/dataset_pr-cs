#include "read_array.h"

void read_array(int array[], int *value, int *length)
{
    scanf("%d",value);
    int i = 0;
    while(getchar()!='\n')
    {
        scanf("%d",&array[i]);
        i++;
        (*length)++;
    }
}
