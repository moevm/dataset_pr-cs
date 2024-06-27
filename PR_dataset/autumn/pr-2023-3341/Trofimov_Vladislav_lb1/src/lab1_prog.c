#include <stdio.h>
#define N 100
#define format "%d\n"

int max(int arr[],int count){
    int max_index = 0;
    for (int i = 1; i < count; i++) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

int min(int arr[],int count){
    int min_index = 0;
    for(int i = 1; i < count; i++) {
        if (arr[i] < arr[min_index]){
            min_index = i;
        }
    }
    return min_index;
}

int diff(int arr[], int count){
    return arr[max(arr,count)] - arr[min(arr,count)];
}

int sum(int arr[],int count){
    int sum = 0;
    int min_index = min(arr,count);
    for(int i = 0; i < min_index;i++){
        sum += arr[i];
    }
    return sum;
}

int output(int command, int count, int *arr) {
    switch(command) {
        case 0:
            printf(format, arr[max(arr,count)]);
            break;
        case 1:
            printf(format, arr[min(arr, count)]);
            break;
        case 2:
            printf(format, diff(arr,count));
            break;
        case 3:
            printf(format, sum(arr,count));
            break;
        default:
            printf("Данные некорректны");
            break;
    }
}

int input_arr(int arr[]){
    int count = 0;
    char space = ' ';
    while (count < N && space == ' '){
        scanf("%d%c", &arr[count],&space);
        count++;
    }
    return count;
}

int input_command(){
    int command;
    scanf("%d", &command);
    return command;
}

int main(){
    int command = input_command();
    int arr[N];
    int count = input_arr(arr);
    output(command,count,arr);
}
