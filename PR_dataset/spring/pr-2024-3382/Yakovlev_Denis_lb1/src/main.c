#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int main()
{
    char** text = (char**)malloc(sizeof(char*));
    char symbol;
    int size_text = 0, len, flag = 1, size_str, step = 50;
    while(flag) 
    {
        len = 0;
        size_str = step;
        text = (char**)realloc(text, sizeof(char*) * (size_text + 1));
        text[size_text] = (char*)malloc(sizeof(char) * step);
        while(1) 
        {
            if (len > size_str)
            {
                size_str += step;
                text[size_text] = (char*)realloc(text[size_text], sizeof(char) * size_str);
            }
            symbol = getchar();
            text[size_text][len] = symbol;
            text[size_text][len + 1] = '\000';
            if (symbol == '\n') 
            {
                text[size_text][len] = '\000';
                break;
            }
            if (!(strcmp(text[size_text], "Fin.\0"))) 
            {
                flag = 0;
                break;
            }
            len++;
        }
        if (flag == 0) 
        {
            size_text++;
            break;
        }
        size_text++;
    }
    
    // REGEX:
    
    char* regular_expression = "([A-Za-z0-9_]+)@[A-Za-z0-9_-]+: *~ *# (.+)";
    regex_t compiled;
    regcomp(&compiled, regular_expression, REG_EXTENDED);
    size_t size_max_arr = 3;
    int size_name, size_command;
    regmatch_t arr_group[size_max_arr];
    for (int i = 0; i < size_text; i++) 
    {
        if (!(regexec(&compiled, text[i], size_max_arr, arr_group, 0))) 
        {
            size_name = arr_group[1].rm_eo - arr_group[1].rm_so;
            size_command = arr_group[2].rm_eo - arr_group[2].rm_so;
            printf("%.*s - ", size_name, text[i] + arr_group[1].rm_so);
            printf("%.*s\n", size_command, text[i] + arr_group[2].rm_so);
        }
    }
    
    
    for(int i = 0; i < size_text; i++)
    {
        free(text[i]);
    }
    free(text);
    return 0;
}