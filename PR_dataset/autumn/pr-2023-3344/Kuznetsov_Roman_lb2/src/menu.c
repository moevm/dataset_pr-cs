#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main(){
    int arr[100]={0};  
    int choice;
    int size=0; 
    
    
    scanf("%d", &choice);

    
    while (size<100 && getchar()!= '\n'){        
        scanf("%d", &arr[size]);
        size++;
    }

    int first_zero_index=index_first_zero(arr, size);
    int last_zero_index=index_last_zero(arr, size);
    if (first_zero_index==-1 || last_zero_index==-1){
        printf("Данные некорректны\n");
        return 0;
    }
    switch (choice){
        case 0: printf("%d\n", first_zero_index); break;
        case 1: printf("%d\n", last_zero_index); break;
        case 2: printf("%d\n", sum_between(arr, size)); break;
        case 3: printf("%d\n", sum_before_and_after(arr, size)); break;
        default: printf("Данные некорректны\n"); break;
    }
    return 0;
}
