#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define STRING_SIZE 2000

int first_negative_index(int count, int dambo[]);
int last_negative_index(int count, int dambo[]);
void sum_between_negatives(int count, int dambo[]);
void sum_before_and_after_negatives(int count, int dambo[]);

int main()
{
        char string[STRING_SIZE];

        fgets(string, STRING_SIZE, stdin);

        if (string[strlen(string) - 1] == '\n') string[strlen(string) - 1] = 0;

        int dambo[100];
        int counter = 0;

        char *istr;

        istr = strtok(string, " ");
        int flow = atoi(istr);

        istr = strtok(NULL, " ");

        while (istr != NULL)
        {
                dambo[counter++] = atoi(istr);
                istr = strtok(NULL, " ");
        }
        switch (flow)
        {
                case(0):
                        printf("%d\n", first_negative_index(counter, dambo));
                        break;
                case(1):
                        printf("%d\n", last_negative_index(counter, dambo));
                        break;
                case(2):
                        sum_between_negatives(counter, dambo);
                        break;
                case(3):
                        sum_before_and_after_negatives(counter, dambo);
                        break;
                default:
                        printf("Данные некорректны\n");
        }
        return 0;
}

int first_negative_index(int counter, int dambo[])
{
        for (int i = 0; i < counter; i++)
        {
                if (dambo[i] < 0) return i;
        }
}

int last_negative_index(int counter, int dambo[])
{
        for (int i = counter - 1; i >= 0; i--)
        {
                if (dambo[i] < 0) return i;
        }
}

void sum_between_negatives(int counter, int dambo[])
{
        int sum = 0;

        for (int i = first_negative_index(counter, dambo); i < last_negative_index(counter, dambo); i++)
        {
                sum += abs(dambo[i]);
        }

        printf("%d\n", sum);
        return;
}

void sum_before_and_after_negatives(int counter, int dambo[])
{
        int sum = 0;

        for (int i = 0; i < first_negative_index(counter, dambo); i++)
        {
                sum += abs(dambo[i]);
        }
        for (int i = last_negative_index(counter, dambo); i < counter; i++)
        {
                sum += abs(dambo[i]);
        }

        printf("%d\n", sum);
        return;
}
