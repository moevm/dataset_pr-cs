#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define BASE 50
#define REGSTR "([a-zA-Z0-9_]{1,})@[a-zA-Z0-9_-]{1,}:\\s{0,}?~\\s{0,}# (.{1,})"
#define ERROR "Error malloc\n"
#define ENDOFSTR '\0'
char* read_sentence()
{
    int capacity = BASE;
    int idx = 0;
    char* sentence = malloc(capacity);
    if (sentence == NULL)
    {
        fprintf(stderr, ERROR);
        exit(1);
    }
    char ch = getchar();
    while (1)
    {
        if (ch == '\n' || ch == EOF || ch == '\0')
        {
            break;
        }
        sentence[idx++] = ch;
        if (idx == capacity - 1)
        {
            capacity += BASE;
            sentence = realloc(sentence, capacity);
            if (sentence == NULL)
            {
                fprintf(stderr, ERROR);
                free(sentence);
                exit(1);
            }
        }
        ch = getchar();
    }
    sentence[idx] = ENDOFSTR;
    return sentence;
}
char** create_array(int *ind)
{
    int capacity = BASE;
    char** array = malloc(sizeof(char*) * capacity);
    if (array == NULL)
    {
        fprintf(stderr, ERROR);
        exit(1);
    }
    int idx=0;
    while (1)
    {
        array[idx] = read_sentence();
        if (strcmp(array[idx], "Fin.") == 0)
        {
            free(array[idx]);
            break;
        }
        idx++;
        if (idx == capacity-2)
        {
            capacity += BASE;
            array = realloc(array, sizeof(char*) * capacity);
            if (array == NULL)
            {
                fprintf(stderr, ERROR);
                for (int i = 0; i < idx; i++)
                {
                    free(array[i]);
                }
                free(array);
                exit(1);
            }
        }
    }
    *ind=idx;
    return array;
}
void just_output(char** array, int ind)
{
    int flaghok=1;
    for (int i = 0; i < ind; i++)
    {
        regex_t reg_compile;
        size_t max_group=3;
        regmatch_t num_of_group[max_group];
        if(regcomp(&reg_compile, REGSTR, REG_EXTENDED))
        {fprintf(stderr,"Can't compile expression\n");
        exit(0);}
        if(regexec(&reg_compile, array[i], max_group, num_of_group,0)==0)
        {
            if(flaghok==1)
            {
                flaghok=0;
                printf("%.*s - %.*s",
                (int)(num_of_group[1].rm_eo-num_of_group[1].rm_so), array[i]+num_of_group[1].rm_so,
                (int)(num_of_group[2].rm_eo-num_of_group[2].rm_so), array[i]+num_of_group[2].rm_so);
            }
            else if(flaghok==0)
            {
                printf("\n%.*s - %.*s",
                (int)(num_of_group[1].rm_eo-num_of_group[1].rm_so), array[i]+num_of_group[1].rm_so,
                (int)(num_of_group[2].rm_eo-num_of_group[2].rm_so), array[i]+num_of_group[2].rm_so);
            }
        }
        regfree(&reg_compile);
        free(array[i]);
    }
    free(array);
}
int main()
{
    int ind=0;
    char** array=create_array(&ind);
    just_output(array,ind);
    return 0;
}