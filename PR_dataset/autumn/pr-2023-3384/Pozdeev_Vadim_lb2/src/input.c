#include <stdio.h>
int input(int * array, int size){
    int length=0;
    for(int i = 0; i!= size; i++)
        {
        char end;
        int val;
        scanf("%d%c", &val, &end);
        array[length] = val;
        length++;
        if(end == '\n')
            {break;}
    }
    return length;
}
