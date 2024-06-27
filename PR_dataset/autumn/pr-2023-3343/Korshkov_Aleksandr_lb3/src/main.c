#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char *start_symbols_delete(char *sentence)
{
    if (sentence[0] == ' ')
    {
        memmove(sentence, sentence + 1, strlen(sentence));
    }
    return sentence;
}

int main()
{
    char **text = malloc(sizeof(char *));
    unsigned int before = 0, after = 0;

    while (1)
    {
        char *sentence = malloc(sizeof(char)), temp = ' ';
        unsigned int count = 0;
        unsigned ch_1 = 0, ch_2 = 0, ch_3 = 0, check_res = 1;
        while (temp != '.' && temp != ';' && temp != '?' && temp != '!')
        {
            temp = getchar();
            if (temp == '\n' || temp == '\t')
            {
                temp = ' ';
            }
            if (temp == ' ')
            {
                ch_1 = 0;
                ch_2 = 0;
                ch_3 = 0;
            }
            if (isalpha(temp))
            {
                ch_1 = 1;
            }
            if (isdigit(temp) && ch_1 == 1)
            {
                ch_2 = 1;
            }
            if (isalpha(temp) && ch_1 == 1 && ch_2 == 1)
            {
                ch_3 = 1;
            }
            if (ch_1 == 1 && ch_2 == 1 && ch_3 == 1)
            {
                check_res = 0;
            }
            sentence[count] = temp;
            count++;
            sentence = realloc(sentence, (count + 1) * sizeof(char));
        }

        sentence[count] = '\0';
        start_symbols_delete(sentence);
        before++;

        if (check_res)
        {
            text[after] = sentence;
            after++;
            text = realloc(text, (after + 1) * sizeof(char *));
        }

        if (strstr(sentence, "Dragon flew away!"))
        {
            break;
        }
    }

    for (int i = 0; i < after; i++)
    {
        printf("%s\n", text[i]);
        free(text[i]);
    }
    free(text);

    printf("Количество предложений до %d и количество предложений после %d\n", before - 1, after - 1);
    return 0;
}
