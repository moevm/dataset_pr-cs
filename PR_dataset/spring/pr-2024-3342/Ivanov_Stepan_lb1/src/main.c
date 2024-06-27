#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

#define BLOCK_SIZE 10


void
error(const char *_msg)
{
    fprintf(stderr, "%s\n", _msg);
    exit(0);

}

void
error_if(bool _cond, const char *_msg)
{
    if (_cond)
        error(_msg);

}

void *
allocator(void *_old, size_t _n, size_t _size)
{
    void *_ptr = realloc(_old, _n * _size);
    error_if(_ptr == NULL, "ERROR: badalloc");
    return _ptr;
    
}


char * 
read_text()
{
    int cap = BLOCK_SIZE;
    char *text = (char*)allocator(NULL, cap, sizeof(char));

    int k = 0;

    char ch = getchar();
    char ch_1 = 'a';
    char ch_2 = 'a';
    char ch_3 = 'a';
    char ch_4 = 'a';

    while(   ch_1 != 'F' 
          || ch_2 != 'i' 
          || ch_3 != 'n' 
          || ch_4 != '.')
    {
        text[k++] = ch;

        if (k == cap-1)
        {
            cap += BLOCK_SIZE;
            text = (char*)allocator(text, cap, sizeof(char));

        }
        
        ch_1 = ch_2;
        ch_2 = ch_3;
        ch_3 = ch_4;
        ch_4 = ch;
        ch = getchar();

    }

    text[k] = '\0';
    return text;

}

char ** 
split_text(char *text, int *k)
{
    int cap = BLOCK_SIZE;
    char **res_text = (char**)allocator(NULL, cap, sizeof(char*));

    char *sentence = strtok(text, "\n");

    while(sentence != NULL)
    {
        int sent_len = strlen(sentence);
        res_text[*k] = (char*)allocator(NULL, sent_len+1, sizeof(char));

        strcpy(res_text[(*k)++], sentence);
        
        if(*k == cap-1)
        {
            cap += BLOCK_SIZE;
            res_text = (char**)allocator(res_text, cap, sizeof(char*));

        }
        
        sentence = strtok(NULL, "\n");
    }
    
    return res_text;

}

int main(int argc, char **argv)
{
    char *text = read_text();
    int k = 0;

    char **res_text = split_text(text, &k);
    const char *regex_pttrn = "(([A-z]*):\\/\\/)?(www.)?([A-z0-9]+([_\\-\\.]+[A-z]+)+)\\/((([A-z]*)\\/)*)([A-z0-9_\\-]+\\.[A-z0-9_\\-]+)";

    regex_t regexCompiled;
    regmatch_t groupArray[BLOCK_SIZE];

    error_if(regcomp(&regexCompiled, regex_pttrn, REG_EXTENDED),
             "ERROR: Could not compile regular expression\n");

    for(int index = 0; index < k; index++)
    {
        if(regexec(&regexCompiled, res_text[index], BLOCK_SIZE, groupArray, 0) == 0)
        {
            for(int j = groupArray[4].rm_so; j < groupArray[4].rm_eo; j++)
                printf("%c",res_text[index][j]);
            
            printf(" - ");

            for(int j = groupArray[9].rm_so; j < groupArray[9].rm_eo; j++)
                printf("%c",res_text[index][j]);
            
            printf("\n");
        }
    }

    free(text);
    
    for(int i = 0; i < k; i++)
        free(res_text[i]);
    
    free(res_text);

    regfree(&regexCompiled);

    return 0;

}