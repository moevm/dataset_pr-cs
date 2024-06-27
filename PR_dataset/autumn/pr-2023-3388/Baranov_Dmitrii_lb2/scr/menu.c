#include<stdio.h>
#include"min.h"
#include"max.h"
#include"sum.h"
#include"diff.h"
#include"Print.h"
#define N 100

int main() {
        int introValues[N];
        int option;
        int len = 0;
        char space =' ';
        scanf("%d", &option);
        while (len < 100 && space == ' ') {
                scanf("%d%c", &introValues[len], &space);
                len++;
        } 
    	  switch (option) { 
                case 0:
                        Print(max(introValues, len));
                        break;
                case 1:
                        Print(min(introValues, len));
                        break;
                case 2:
                        Print(diff(introValues, len));
                        break;
                case 3:
                        Print(sum(introValues, len));
                        break;
                default:  
            	           printf("Данные некорректны\n"); break;
        }
}
