#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STEP 10

int main()
{
    char **splitted_text = (char **)malloc(sizeof(char *) * STEP);
    int len = 0, max_len = STEP;
    char symbol;
    for (int i = 0; i < STEP; i++)
    {
        splitted_text[i] = (char *)malloc(sizeof(char) * STEP);
    }
    do
    {
        int i = 0;
        int max_len_str = STEP;
        if (len > max_len - 1)
        {
            max_len += STEP;
            splitted_text = (char **)realloc(splitted_text, sizeof(char *) * max_len);
            for (int k = len; k < max_len; k++)
            {
                splitted_text[k] = (char *)malloc(sizeof(char) * STEP);
            }
        }
        do
        {
            if (i >= max_len_str)
            {
                max_len_str += STEP;
                splitted_text[len] = (char *)realloc(splitted_text[len], sizeof(char) * max_len_str);
            }
            symbol = getchar();
            if (symbol == '\n')
                symbol = ' ';
            splitted_text[len][i] = symbol;
            i++;
        } while (symbol != ';' && symbol != '.' && symbol != '?' && symbol != '!');
        splitted_text[len][i] = '\0';
        len++;
    } while (symbol != '!');
    for (int i = 1; i < len; i++)
    {
        if (isspace(splitted_text[i][0]) && isspace(splitted_text[i][1]))
        {
            splitted_text[i][1] = '\n';
        }
        else
        {
            if (isspace(splitted_text[i][0]))
                splitted_text[i][0] = '\n';
        }
    }
    int new_len = 0;
    for (int i = 0; i < len; i++)
    {
        if (strchr(splitted_text[i], '7') == NULL)
        {
            printf("%s", splitted_text[i]);
            new_len++;
        }
    }
    printf("\nКоличество предложений до %d и количество предложений после %d\n", len - 1, new_len - 1);
    for (int i = 0; i < len; i++)
    {
        free(splitted_text[i]);
    }
    free(splitted_text);
    return 0;
}
