#include <stdio.h>
#include "min.h"
#include "max.h"
#include "diff.h"
#include "sum.h"
int main(){
    int selection;
    scanf("%d", &selection);
    int arr[200];
    int quantity;
    for(int i = 0;i<200;i++){
        char letter;
        scanf("%d%c", &arr[i], &letter);
        if(letter == '\n'){
            quantity = i;
            break;
        }
    }
    switch(selection){
        case 0:
            printf("%d\n",max(arr, quantity));
            break;
        case 1:
            printf("%d\n",min(arr, quantity));
            break;
        case 2:
            printf("%d\n",diff(arr, quantity));
            break;
        case 3:
            printf("%d\n",sum(arr, quantity));
            break;
        default: 
            printf("Данные некорректны\n");
    }
        return 0;
}
