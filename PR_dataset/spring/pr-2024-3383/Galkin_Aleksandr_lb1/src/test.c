#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>
#define STEP 8
typedef struct Text
{
    char **text;
    int length;
} Text;

Text get_text();
void free_memory(Text text);

int main()
{
    Text text = get_text();
    regex_t re;
    if (regcomp(&re, "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+[:] ?[~] ?[#] (.*)", REG_EXTENDED))
    {
        fprintf(stderr, "Compile unsuccess;\n");
        exit(1);
    };
    int o = 0;
    for (int i = 0; i < text.length; i++)
    {
        regmatch_t match[3];
        int value = regexec(&re, text.text[i], 3, match, 0);
        if (value != 0)
        {
            continue;
        }
        else
        {
            if (o != 0)
                printf("\n");
            for (int j = match[1].rm_so; j < match[1].rm_eo; j++)
            {
                printf("%c", text.text[i][j]);
            }
            printf(" - ");
            for (int j = match[2].rm_so; j < match[2].rm_eo; j++)
            {
                printf("%c", text.text[i][j]);
            }
            o++;
        }
    }
    free_memory(text);
    regfree(&re);
    return 0;
}

Text get_text()
{
    char **text = (char **)malloc(sizeof(char *)), c;
    text[0] = (char *)malloc(sizeof(char) * STEP);
    int length = 0, flag = 0;
    while (1)
    {
        int maxlen = STEP, h = 0;
        do
        {
            if (h >= maxlen - 2)
            {
                maxlen += STEP;
                char *tmp = (char *)realloc(text[length], maxlen * sizeof(char));
                if (tmp)
                {
                    text[length] = tmp;
                }
                else
                {
                    fprintf(stderr, "Reallocation error;\n");
                    exit(2);
                }
            }
            c = getchar();
            text[length][h] = c;
            if (strncmp(text[length], "Fin.", 4) == 0)
            {
                flag = 1;
                break;
            }
            h++;
        } while (c != '\n');
        text[length][h - 1] = '\0';
        if (strncmp(text[length], "Fin.", 4) == 0 || flag == 1)
        {
            length++;
            break;
        }
        length++;
        char **temp = (char **)realloc(text, (length + 1) * sizeof(char *));
        if (temp)
        {
            text = temp;
            temp[length] = (char *)malloc(sizeof(char) * STEP);
        }
        else
        {
            fprintf(stderr, "Reallocation error;\n");
            exit(2);
        }
    }
    Text received = {text, length};
    return received;
}

void free_memory(Text text)
{
    for (int i = 0; i < text.length; i++)
    {
        free(text.text[i]);
    }
    free(text.text);
}