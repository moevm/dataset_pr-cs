#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define STRING_TERMINATOR '\0'
#define TEXT_TERMINATOR "Fin."
#define CHUNK 256

const char *regex_pattern = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.*)";

void input(char **);
int end_of_text(char *);
void check_string(char *, regex_t);
void print_group(char *, regmatch_t);
void output(char *, regmatch_t *);

int main(void) 
{
    regex_t re;
    regcomp(&re, regex_pattern, REG_EXTENDED);
    
    char *string;
    while(1) {
        string = NULL;
        input(&string);
        if (end_of_text(string))
            break;
        check_string(string, re);
        
        if (string != NULL)
            free(string);
    }
        
    regfree(&re);
    return 0;
}

void input(char **string) 
{
    size_t size = 0, capacity = 0;
	char ch = 0;
	
	while (ch != '\n') {
		ch = getchar();
		
		while (size + 1 >= capacity) {
			capacity += CHUNK;
			*string = (char *)realloc(*string, capacity * sizeof(char));
		}
		
		(*string)[size++] = ch;
		(*string)[size] = STRING_TERMINATOR;
		
		if (end_of_text(*string)) 
		    break;
	}
}

int end_of_text(char *string)
{
    return (strcmp(string, TEXT_TERMINATOR) == 0);
}

void check_string(char *string, regex_t re)
{
    regmatch_t groups[re.re_nsub + 1];
    
    if (regexec(&re, string, re.re_nsub + 1, groups, 0) == 0)
        output(string, groups);
}

void print_group(char *string, regmatch_t group) 
{
    for (size_t i = group.rm_so; i < group.rm_eo; i++)
        printf("%c", string[i]);
}

void output(char *string, regmatch_t *groups) 
{
    print_group(string, groups[1]);
    printf(" - ");
    print_group(string, groups[2]);
}