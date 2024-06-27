#include <stdio.h>

#include "index_first_negative.h"
#include "index_first_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

#define PATTERN_ANSWER "%d\n"

#define STR_SIZE 65536
#define ARR_SIZE 21

char str[STR_SIZE];

size_t fill_str();
size_t fill_arr(int[]);

size_t check_arr(int[], size_t);


int main(int argc, char **argv)
{
    fill_str();

    main_logic();


    return 0;

}


void
main_logic()
{
    int arr[ARR_SIZE];

    size_t len_arr = fill_arr(arr);

    size_t _flag = check_arr(arr, len_arr);

    if (!_flag)
    {
        printf("%s\n", "Данные некорректны");
        return;
    }

    switch (arr[0])
    {
    case 0:
        printf(PATTERN_ANSWER, index_first_negative(arr, len_arr) - 1);
        break;
    
    case 1:
        printf(PATTERN_ANSWER, index_last_negative(arr, len_arr) - 1);
        break;
    
    case 2:
        printf(PATTERN_ANSWER, multi_between_negative(arr, len_arr));
        break;
    
    case 3:
        printf(PATTERN_ANSWER, multi_before_and_after_negative(arr, len_arr));
        break;
    
    default:
        printf("%s\n", "Данные некорректны");
        break;

    }
}


size_t
fill_str()
{
    int iter = 0;

    char ch = getchar();
    while (ch != '\n')
    {
        str[iter++] = ch;
        ch = getchar();

    }
    
    str[iter] = '\0';

    return iter + 1;

}


size_t
fill_arr(int arr[])
{
    int iter_arr = 0;
    char *iter_str = str;
    int n, cnt_chars;

    while (sscanf(iter_str, "%d%n", &n, &cnt_chars) == 1)
    {
        arr[iter_arr++] = n;
        iter_str += cnt_chars;

    }

    return iter_arr;
    
}


size_t 
check_arr(int arr[], size_t len_arr)
{
    for (size_t i = 0; i < len_arr; ++i)
    {
        if (arr[i] < 0)
            return 1;

    }

    return 0;

}

