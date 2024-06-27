#include <stdio.h>
#include <stdlib.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int main()
{
    int nomer;
    int massive[100];
    char probel;
    int len = 0;
    scanf("%d%c", &nomer, &probel);
    do {
        scanf("%d%c", &massive[len], &probel);
        len ++;
    } while(probel != '\n');
    
    int x, y, z, w;
    x = massive[max(massive, len)];
    y = massive[min(massive, len)];
    z = diff(massive, len);
    w = sum(massive, min(massive,len));
    
    switch(nomer){
        case 0: 
            printf("%d", x); 
            break;
        case 1: 
            printf("%d", y);
            break;
        case 2: 
            printf("%d", z);
            break;
        case 3: 
            printf("%d", w);
            break;
        default: 
            printf("Данные некорректны");
    } 
    return 0;
}
