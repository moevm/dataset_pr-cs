#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int processing(char *str);
int main()
{
    int amount_after = 0;
    int text_cap = 10;
    int str_cap = 20;
    int count = 0;

    char **text = malloc(sizeof(char *) * text_cap);
    char *in = malloc(sizeof(char));
    do
    {
        char *str = malloc(str_cap * sizeof(char));
        str[0] = '\0';
        int len = 0;
        do
        {
            *in = getchar();
            if ((*in == ' ' || *in == '\t') && len == 0)
                continue;
            strcat(str, in);

            if (len >= str_cap - 3)
            {
                // printf("%d %p\n", str_cap, str);
                str_cap += 10;
                str = realloc(str, str_cap);
            }

            len++;
        } while (*in != '.' && *in != ';' && *in != '?' && *in != '!');

        if (count >= text_cap - 3)
        {
            text_cap += 10;
            text = realloc(text, text_cap * sizeof(char *));
        }
        text[count] = str;
        // printf("%d %s\n", len, text[count-1]);
        if (processing(str))
        {
            printf("%s\n", text[count]);
            amount_after++;
        }
        count++;

    } while (*in != '!');
    printf("Количество предложений до %d и количество предложений после %d", count - 1, amount_after - 1);
    for (int i = 0; i < count; i++)
    {
        free(text[i]);
    }
    free(text);
}

int processing(char *str)
{
    for (int i = 0; str[i] != '\0' && i < strlen(str) - 4; i++)
    {
        if (str[i] == ' ' && str[i + 1] == '5' && str[i + 2] == '5' && str[i + 3] == '5' && str[i + 4] == ' ')
        {
            return 0;
        }
        if (str[i] == '5' && str[i + 1] == '5' && str[i + 2] == '5' && str[i + 3] == ' ')
        {
            return 0;
        }
        if (str[i] == ' ' && str[i + 1] == '5' && str[i + 2] == '5' && str[i + 3] == '5' && (str[i + 4] == ' ' || str[i + 4] == '.' || str[i + 4] == ';' || str[i + 4] == '?'))
        {
            return 0;
        }
    }
    return 1;
}