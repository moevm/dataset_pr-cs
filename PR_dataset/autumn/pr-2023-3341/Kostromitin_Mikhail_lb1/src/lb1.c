#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define RESULT "%d\n"
#define STRING_SIZE 1500

int index_first_negative(int a, int b[]);
int index_last_negative(int a, int b[]);
int sum_between_negative(int a, int b[]);
int sum_before_and_after_negative(int a, int b[]);
void input_output();

int main()
{
        input_output();
        return 0;
}

void input_output()
{
        char string[STRING_SIZE];

        fgets(string, STRING_SIZE, stdin);

        if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = 0;

        int array[100];
        int size = 0;

        char *current_str;

        current_str = strtok(string, " ");
        int func_type = atoi(current_str);

        current_str = strtok(NULL, " ");

        while (current_str != NULL)
        {
                array[size++] = atoi(current_str);
                current_str = strtok(NULL, " ");
        }
        switch (func_type)
        {
                case(0):
                        printf(RESULT, index_first_negative(size, array));
                        break;
                case(1):
                        printf(RESULT, index_last_negative(size, array));
                        break;
                case(2):
                        printf(RESULT, sum_between_negative(size, array));
                        break;
                case(3):
                        printf(RESULT, sum_before_and_after_negative(size, array));
                        break;
                default:
                        printf("Данные некорректны\n");
        }

}

int index_first_negative(int size, int array[])
{
        for (int i = 0; i < size; i++)
        {
                if (array[i] < 0) return i;
        }
}

int index_last_negative(int size, int array[])
{
        for (int i = size - 1; i >= 0; i--)
        {
                if (array[i] < 0) return i;
        }
}

int sum_between_negative(int size, int array[])
{
        int sum = 0;

        for (int i = index_first_negative(size, array); i < index_last_negative(size, array); i++)
        {
                sum += abs(array[i]);
        }

        return sum;
}

int sum_before_and_after_negative(int size, int array[])
{
        int sum = 0;

        for (int i = 0; i < index_first_negative(size, array); i++)
        {
                sum += abs(array[i]);
        }
        for (int i = index_last_negative(size, array); i < size; i++)
        {
                sum += abs(array[i]);
        }

        return sum;
}
