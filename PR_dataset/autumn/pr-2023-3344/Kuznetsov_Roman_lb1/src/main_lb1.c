#include <stdio.h>
#include <stdlib.h>

int index_first_zero(int arr[], int size){
    for (int i=0;i<size;i++) {
        if (arr[i] == 0)
            return i;
    }
    return -1;    
}

int index_last_zero(int arr[], int size){    
    int last_zero_index=-1;
    for (int i=0; i<size; i++){
        if (arr[i]==0)
            last_zero_index = i;
    }
    return last_zero_index;
}

int sum_between(int arr[], int size, int start, int end) {
    if (start>= size|| end>=size || start > end)
        return 0;

    int sum = 0;
    for (int i=start; i<=end; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

void processArray(int arr[], int size, int choice) {
    int first_zero_index=index_first_zero(arr, size);
    int last_zero_index=index_last_zero(arr, size);
    if (first_zero_index==-1 || last_zero_index==-1){
        printf("Данные некорректны\n");
        return;
    }
    switch (choice){
        case 0:
            printf("%d\n",first_zero_index);
            break;
        case 1:
            printf("%d\n",last_zero_index);
            break;
        case 2:
            printf("%d\n",sum_between(arr, size, first_zero_index + 1, last_zero_index - 1));
            break;
        case 3:
            printf("%d\n",sum_between(arr, size, 0, first_zero_index - 1) + sum_between(arr, size, last_zero_index + 1, size - 1));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}

int main(){
    int arr[100]={0};  
    int choice;
    int size=0; 
    
    
    scanf("%d", &choice);
    
    if (choice<0 || choice>3){
        printf("Данные некорректны\n");
        return 0;
    }             
    
    
    
    while (size<100 && getchar()!= '\n'){        
        scanf("%d", &arr[size]);
        size++;
    }
    
    if (size<=0 || size>100){
        printf("Данные некорректны\n");     
        return 0;
    }
    
    processArray(arr,size,choice);

    return 0;
}
