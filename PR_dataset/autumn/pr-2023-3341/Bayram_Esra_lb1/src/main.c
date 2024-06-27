#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGHT 100

int max(int arr[], int size) {
    int max_value = arr[0];
    int i = 1;
    
    while (i < size) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
        i++;
    }
    
    return max_value;
}



int min(int arr[], int size) {
    int min_value = arr[0];
    int i = 1;
    
    while (i < size) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
        i++;
    }
    
    return min_value;
}



int diff(int arr[], int size)
{
    return max(arr, size) - min(arr, size);
}

int sum(int arr[], int size)
{
    int min_index = 0;

    for (int i = 1; i < size; i++)
    {
        if (arr[i] < arr[min_index])
        {
            min_index = i;
        }
    }

    int sum = 0;
    for (int i = 0; i < min_index; i++)
    {
        sum += arr[i];
    }

    return sum;
}

int main()
{
    int array[MAX_LENGHT];
    int input;
    int size_array = 0;
    char space = ' ';

    scanf("%d", &input);
    while (size_array < MAX_LENGHT && space == ' ')
    {
        scanf("%d%c", &array[size_array], &space);
        size_array++;
    }

    switch (input)
    {
    case 0:
        printf("%d\n", max(array, size_array));
        break;
    case 1:
        printf("%d\n", min(array, size_array));
        break;
    case 2:
        printf("%d\n", diff(array, size_array));
        break;
    case 3:
        printf("%d\n", sum(array, size_array));
        break;
    default:
        printf("Данные некорректны\n");
        break;
    }
}
