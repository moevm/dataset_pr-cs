#include <stdio.h>
#include <stdlib.h>

int max(int massive[], int len){
    int max = massive[0];
    int index = 0;
    for(int i = 0; i < len; i++)
    {
        if(massive[i] > max) {
            max = massive[i];
            index = i;
        }
    }
    return(index);
}

int min(int massive[], int len){
    int min = massive[0];
    int index = 0;
    for(int i = 0; i < len; i++)
    {
        if(massive[i] < min) {
            min = massive[i];
            index = i;
        }
    }
    return(index);
}


int diff(int a, int b){
    return (a - b);
}

int sum(int massive[], int index){
    int sum = 0;
    for (int i=0; i < index; i++){
        sum += massive[i];
    }
    return sum;
}

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
    z = diff(x,y);
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
