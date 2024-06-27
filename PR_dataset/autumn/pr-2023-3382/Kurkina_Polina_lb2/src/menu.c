#include <stdio.h> 
#include <stdlib.h> 
#include "Solution.h"
int main()
{
    int num, ans;
    int Mas[100];
    char space;
    scanf("%d%c", &num, &space);
    int i = 0, len = 0;
    do{
        scanf("%d%c", &Mas[i], &space);
        i ++;
        len ++;
    } while(space != '\n');
    Solution(num, Mas, len);
    
    return 0;
}
