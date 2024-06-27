#include <stdio.h>
#include <stdlib.h>
#include "sum.h"
#include "abs_min.h"
#include "abs_max.h"
#include "diff.h"
int main(){
    int n;
    scanf("%d", &n);
    int massiv[100];
    int y =0;
    
    while(y <= 100 && scanf("%d", &massiv[y]) ==1){
        y++;
        
        if(getchar() == '\n'){
            break;
        }
    }
    int mas[y];
    
    for(int i=0; i < y; i++){
        
        mas[i] = massiv[i];}
    
    int N = y;
    switch(n)
    {
      case 0: printf("%d\n", abs_max(N, mas)); break;
      case 1: printf("%d\n", abs_min(N, mas)); break;
      case 2: printf("%d\n", diff(N, mas)); break;
      case 3: printf("%d\n", sum(N, mas)); break;
      default: printf("Данные некорректны \n"); break;
       
    }
    
    
}
