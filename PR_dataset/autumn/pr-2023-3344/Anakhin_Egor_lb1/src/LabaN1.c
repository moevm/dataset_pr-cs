#include <stdio.h>

int index_first_negative(int arr[], int len);
int index_last_negative(int arr[], int len);
int multi_between_negative(int arr[], int len);
int multi_before_and_after_negative(int arr[], int len);

int main()
{
    int type;
    int last_elem = 0;
    scanf("%d", &type);
    int array[20];

    for (int i = 0; i < 20; i++)
    {
        last_elem++;
        if (scanf("%d", &array[i]) == 0 || getchar() == '\n')
        {
            break;
        }
    }

    switch (type)
    {
    case 0:
        printf("%d\n", index_first_negative(array, last_elem));
        break;
    case 1:
        printf("%d\n", index_last_negative(array, last_elem));
        break;
    case 2:
        printf("%d\n", multi_between_negative(array, last_elem));
        break;
    case 3:
        printf("%d\n", multi_before_and_after_negative(array, last_elem));
        break;
    default:
        printf("Данные некорректны");
        break;
    }

    return 0;
}

int index_first_negative(int arr[], int len)
{
    int return_value = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] < 0)
        {
            return_value = i;
            break;
        }
    }
    return return_value;
}

int index_last_negative(int arr[], int len)
{
    int return_value = 0;
    for (int i = 0; i < len; i++)
    {
        if (arr[i] < 0)
        {
            return_value = i;
        }
    }
    return return_value;
}

int multi_between_negative(int arr[], int len)
{
    int return_value = 1;
    for (int i = index_first_negative(arr, len); i < index_last_negative(arr, len); i++)
    {
        return_value *= arr[i];
    }
    return return_value;
}

int multi_before_and_after_negative(int arr[], int len)
{
    int return_value = 1;
    for (int i = 0; i < index_first_negative(arr, len); i++)
    {
        return_value *= arr[i];
    }

    for (int i = index_last_negative(arr, len); i < len; i++)
    {
        return_value *= arr[i];
    }

    return return_value;
}