# include <stdio.h>

int index_first_negative(int arr[], int amount) {
    for (int i = 0; i < amount; i++){
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1;
} 

int index_last_negative(int arr[], int amount){
    for (int i = amount - 1; i >= 0; i--){
        if (arr[i] < 0){
            return i;
        }
    }
    return -1;
}

int multi_between_negative(int arr[], int amount){
    int start = index_first_negative(arr, amount);
    int end = index_last_negative(arr, amount);
    if (start == -1 || end == -1){
        return 0;
    }
    int result = 1;
    for (int i = start; i < end; i++){
        result *= arr[i];
    }
    return result;
}

int multi_before_and_after_negative(int arr[], int amount){
    int start = index_first_negative(arr, amount);
    int end = index_last_negative(arr, amount);
    if (start == -1 || end == -1){
        return 0;
    }
    int result = 1, before = 0;
    int after = end;
    while (before < start){
        result *= arr[before];
        before++;
    }
    while (after < amount){
        result *= arr[after];
        after++;
    }
    return result;
}

int main(){
    int arr[20];
    int choice;
    scanf("%d", &choice);
    int i = 0;
    char space =' ';
    while (i < 20 && space == ' ') {
        scanf("%d%c", &arr[i], &space);
        i++;
    }
    switch(choice){
        case 0:
            printf("%d\n", index_first_negative(arr, i));
            break;
        case 1: 
            printf("%d\n", index_last_negative(arr, i));
            break;
        case 2: 
            printf("%d\n", multi_between_negative(arr, i));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(arr, i));
            break;
        default:
            printf("Данные некорректны");
    }
    return 0;
}