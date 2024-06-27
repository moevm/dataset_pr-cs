#include <stdio.h>

int getMax(int arr[], int length) {
    int max = 0;
    for (int i = 0; i < length; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int getMin(int arr[], int length) {
    int min = 100;
    for (int i = 0; i < length; i++) {
        if(arr[i] < min) {
            min = arr[i];
        }
    }
    return (min);
}

int getDiff(int arr[], int length) {
    return getMax(arr, length) - getMin(arr, length);
}

int getSum(int arr[], int length) {
    int min = getMin(arr, length);
    int i = 0, sum = 0;
    while (arr[i] != min) {
        sum += arr[i];
        i++;
    }
    return sum;
}

int main()
{
    int value, arr[100], len = 0;
    scanf("%d", &value);
    
    for (int i = 0; i < 100; i++) {
        if (getchar() != '\n') {
            scanf("%d", &arr[i]);
            len++;
        }
        else break;
    }
    
    switch(value) {
        case 0:
            printf("%d\n", getMax(arr, len));
            break;
        case 1:
            printf("%d\n", getMin(arr, len));
            break;
        case 2:
            printf("%d\n", getDiff(arr, len));
            break;
        case 3:
            printf("%d\n", getSum(arr, len));
            break;
        default:
            printf("Данные некорректны");
        
    }

    return 0;
}
