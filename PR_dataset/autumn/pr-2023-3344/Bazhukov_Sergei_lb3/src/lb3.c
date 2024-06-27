#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    // put your code here
    int len = 0;
    int full_len = 0;
    char **text = (char **)malloc(sizeof(char *) * 2000);
    char *a = malloc(sizeof(char));
    do
    {
        int str_len = 0;
        char *stroka = (char *)malloc(sizeof(char) * 2000);
        stroka[0] = '\0';
        do
        {
            *a = getchar();
            if (str_len == 0 && (*a == ' ' || *a == '\t'))
                continue;
            else
                strcat(stroka, a);
            str_len++;
        } while (*a != '.' && *a != ';' && *a != '?' && *a != '!');
        if (*a != '?')
        {
            text[len] = stroka;
            len++;
        }
        else
            free(stroka);
        full_len++;
    } while (*a != '!');
    for (int i = 0; i < len; i++)
    {
        printf("%s\n", text[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d", full_len-1, len-1);
    return 0;
}
