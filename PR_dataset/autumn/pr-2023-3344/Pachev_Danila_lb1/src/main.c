#include <stdio.h>
#include <stdlib.h>
int index_first_negative_func(int arr[], int count){
    int first_negative_index;
    for (int i = 0;i<count;i++){
        if (arr[i]<0){
            first_negative_index = i;
            break;
        }
    }
    return first_negative_index;
}

int index_last_negative_func(int arr[],int count){
    int last_negative_index;
    for (int i = count;i>=0;i--){
        if (arr[i]<0){
            last_negative_index = i;
            break;
        }
    }
    return last_negative_index;
}

int sum_between_negative_func(int arr[], int count){
    int sum_between_negative = 0;
    int first_negative_index = index_first_negative_func(arr, count);
    int last_negative_index = index_last_negative_func(arr, count);

    for (int i = first_negative_index;i<last_negative_index;i++){
        sum_between_negative+=abs(arr[i]);
    }
    return sum_between_negative;
}
int sum_before_and_after_negative_func(int arr[], int count){
    int all_arr_sum = 0;
    int sum_between_negative = sum_between_negative_func(arr, count);
    for (int i = 0;i<=count;i++){
        all_arr_sum+=abs(arr[i]);
    }
    return all_arr_sum-sum_between_negative;
    
    
}

int main(void){
    int arr[100]={0};
    int count = -1;
    int option_number;
    int number;
    do{
        scanf("%d",&number);
        if (count==-1){
            option_number = number;
            count++;
        }
        else{
            arr[count] = number;
            count++;
        }
    }while (getchar()!='\n');
    switch (option_number){
        case 0:
            printf("%d\n",index_first_negative_func(arr, count));
            break;
        case 1:
            printf("%d\n",index_last_negative_func(arr, count));
            break;
        case 2:
            printf("%d\n",sum_between_negative_func(arr, count));
            break;
        case 3:
            printf("%d\n",sum_before_and_after_negative_func(arr, count));
            break;
        default:
            printf("Данные некорректны\n");
    }
    
    return 0;
}
