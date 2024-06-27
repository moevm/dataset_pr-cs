#include <stdlib.h>
#include <stdio.h>

int enter_array_values(int *array)
{
    int array_length = 0;
    do
    {
        scanf("%d", &array[array_length]);
        array_length++;
    } while (getchar() != '\n');
    return array_length;
}

int index_first_even(int *array, int array_length)
{
    for (int i = 0; i < array_length; i++)
    {
        if (array[i] % 2 == 0)
            return i;
    }

    return -1;
}

int index_last_odd(int *array, int array_length)
{
    for (int i = array_length - 1; i >= 0; i--)
    {
        if (array[i] % 2 != 0)
            return i;
    }

    return -1;
}

int sum_between_even_odd(int *array, int array_length)
{
    int sum = 0;

    int left_bound = index_first_even(array, array_length);
    int right_bound = index_last_odd(array, array_length);
    for (int i = left_bound; i < right_bound; i++)
    {
        sum += abs(array[i]);
    }

    return sum;
}

int sum_before_even_and_after_odd(int *array, int array_length)
{
    int sum = 0;

    int left_bound = index_last_odd(array, array_length);
    for (int i = left_bound; i < array_length; i++)
    {
        sum += abs(array[i]);
    }

    int right_bound = index_first_even(array, array_length);
    for (int i = 0; i < right_bound; i++)
    {
        sum += abs(array[i]);
    }

    return sum;
}

int main()
{
    int mode = -1;
    scanf("%d", &mode);

    int array[100] = {0};
    int array_length = enter_array_values(array);

    int result = -1;
    switch (mode)
    {
    case 0:
        result = index_first_even(array, array_length);
        break;

    case 1:
        result = index_last_odd(array, array_length);
        break;

    case 2:
        result = sum_between_even_odd(array, array_length);
        break;

    case 3:
        result = sum_before_even_and_after_odd(array, array_length);
        break;

    default:
        printf("Данные некорректны\n");
        return 0;
    }

    printf("%d\n", result);
    return 0;
}
