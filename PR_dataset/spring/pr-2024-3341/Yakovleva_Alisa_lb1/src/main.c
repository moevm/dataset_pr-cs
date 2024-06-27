#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_STRING_LENGTH 100
#define LAST_STRING "Fin."
#define END_STRING '\0'

void read_string(char* current_string)
{
    int i = -1;
    do
    {
        scanf ("%c", &current_string[++i]);
    }while (current_string[i] != '\n');
    current_string[++i] = END_STRING;
}

void output_matched_string(char* current_string, regmatch_t* group_array)
{
    current_string[group_array[1].rm_eo] = END_STRING;
    current_string[group_array[3].rm_eo] = END_STRING;
    printf("%s - %s\n", current_string + group_array[1].rm_so, current_string + group_array[3].rm_so);
}

int main ()
{
    char* current_string = malloc(MAX_STRING_LENGTH*sizeof(char));
    char* regex_string = "(\\w+)@(\\w|-)+: *~ *# ([^\n]+)\n$";
    regex_t regex_compiled;

    if (regcomp(&regex_compiled, regex_string, REG_EXTENDED) == 0)
    {
        regmatch_t group_array[regex_compiled.re_nsub + 1];
        while (strncmp(current_string, LAST_STRING, strlen(LAST_STRING)))
        {
            read_string(current_string);
        	if (regexec(&regex_compiled, current_string, regex_compiled.re_nsub + 1, group_array, 0) == 0)
        	    output_matched_string(current_string, group_array);
        }
    }
    
    free(current_string);
    
    return 0;
}
