#include <stdio.h>

#include <stdlib.h>

int arr[100];

int countersize = 0, choice;

int index_first_negative(int arr[], int n) {
    
    for (int i = 0; i < n; i++) {
        
        if (arr[i] < 0) {
            
            return i;
            
        }
        
    }
    
}

int index_last_negative(int arr[], int n) {
    
    for (int i = n - 1; i >= 0; i--) {
        
        if (arr[i] < 0) {
            
            return i;
        }
    }
}

int sum_between_negative(int arr[], int n) {
    
    int first_negative_index = index_first_negative(arr, n);
    
    int last_negative_index = index_last_negative(arr, n);
    
    int summa = 0;
    
    for(int i = first_negative_index; i < last_negative_index; i++){
        
        summa += abs(arr[i]);
        
    }
    
    return summa;
    
}

int sum_before_and_after_negative(int arr[], int n) {
    
    int first_negative_index = index_first_negative(arr, n);
    
    int last_negative_index = index_last_negative(arr, n);
    
    int summa = 0;
    
    for (int i=0; i < first_negative_index; i++){
        
        summa += abs(arr[i]);
        
    }
    for (int i = last_negative_index; i < n; i++){
        
        summa += abs(arr[i]);
        
    }
    
    return summa;
}

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
