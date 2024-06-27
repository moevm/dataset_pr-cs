#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int counter_before = 0;
    int counter_after = 0;

    int number_letters = 1;
    char c = getchar();
    char *str = malloc(number_letters);
    str[0] = c;
    while (!(strstr(str, "Dragon flew away!")))
    {
        c = getchar();
        str = realloc(str, number_letters + 2);
        str[number_letters++] = c;
        str[number_letters] = '\0';
    }
    char *str_before = malloc(number_letters);
    int i = 0;
    str_before[i++] = str[0];
    for (int j = 1; j < number_letters; j++)
    {
        if (isspace(str[j]) && ((str[j - 1] == '.') || (str[j - 1] == ';')))
        {
            str_before[i++] = '\n';
            counter_before++;
            counter_after++;
        }
        else if (str[j] == '?')
        {
            int first_index = j;
            while ((str_before[first_index] != '.') && (str_before[first_index] != ';') && (first_index != -1))
            {
                str_before[first_index--] = '\0';
            }
            j++;
            i = first_index + 1;
            if (first_index != -1) {
                str_before[i++] = '\n';
            }
            str_before[i] = str[j];
            str_before[i + 1] = '\0';
            counter_before++;
        }
        else
            str_before[i++] = str[j];

    }
    for (i = 0; str_before[i]; i++)
        printf("%c", str_before[i]);
    printf("\nКоличество предложений до %d и количество предложений после %d", counter_before, counter_after);
    free(str);
    free(str_before);
    return 0;
}
