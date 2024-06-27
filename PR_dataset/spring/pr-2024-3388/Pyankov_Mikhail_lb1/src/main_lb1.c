#include<stdlib.h>
#include<stdio.h>
#include<regex.h>
#include<string.h>
#define REGEX_STRING "([A-z0-9]+[A-z0-9_]*:\\/\\/)?(www.)?(([A-z0-9]+[A-z0-9_]*\\.)+([A-z]+))\\/([A-z0-9_]+\\/)*([A-z0-9_]+\\.[A-z0-9_]+)"
#define STR_SIZE 500
#define STOP "Fin."
#define MAX_GROUPS 8
#define SITE_NAME_GROUP 3
#define FILE_NAME_GROUP 7

char** text_input(int* text_index)
{
    char** text;
    text = calloc(STR_SIZE,sizeof(char*));
    char* str;
    do
    {
        str = calloc(STR_SIZE,sizeof(char));
        fgets(str, STR_SIZE, stdin);
        text[*text_index] = str;
        *text_index+=1;
    }while (strncmp(str, STOP, strlen(STOP)));
    return text;
}

void url_seek_func(char** text, int* text_index)
{
    regex_t regex_compiled;
    regmatch_t group_array[MAX_GROUPS];

    regcomp(&regex_compiled, REGEX_STRING, REG_EXTENDED);

    for(int k = 0 ; k < *text_index; k++)
    {
        if (regexec(&regex_compiled, text[k], MAX_GROUPS, group_array, 0) == 0)
        {
            for (int i = 0; i <= MAX_GROUPS; i++)
            {
                if(i==SITE_NAME_GROUP||i==FILE_NAME_GROUP)
                {
                    for(int j=group_array[i].rm_so;j<group_array[i].rm_eo;j++)
                    printf("%c",text[k][j]);
                    if(i==SITE_NAME_GROUP)
                    printf(" - ");
                    else
                    printf("\n");
                }
            }
        }
    }
    regfree(&regex_compiled);
}

int main ()
{
    int text_index = 0;
    char** text = text_input(&text_index);
    url_seek_func(text, &text_index);
    return 0;
}