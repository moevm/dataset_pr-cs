#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

int arr[100];

int countersize = 0, choice;

int main() {
    
    scanf("%d", &choice);
    
    while(getchar() != '\n'){ 
        
    scanf("%d", &arr[countersize]);
    
        countersize ++;
    }
    
    switch (choice) {
        
        case 0:
        
            printf("%d\n", index_first_negative(arr, countersize));
            
            break;
            
        case 1:
        
            printf("%d\n", index_last_negative(arr, countersize));
            
            break;
            
        case 2:
        
            printf("%d\n", sum_between_negative(arr, countersize));
            
            break;
            
        case 3:
        
            printf("%d\n", sum_before_and_after_negative(arr, countersize));
            
            break;
            
        default:
        
            puts("Данные некорректны\n");
            
    }

    return 0;
    
}
