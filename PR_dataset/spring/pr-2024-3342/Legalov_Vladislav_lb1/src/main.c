#include <stdio.h>
#include <string.h>
#include <regex.h>

#define REGEX_STRING "([A-Za-z0-9_]+)@[A-Za-z0-9_-]+: ?~ ?\\# (.+\n)"
#define LAST_STRING "Fin."
#define SIZE_BUFFER 100
#define COUNT_GROUPS 3

void print_group(char *str, regmatch_t *groups, int group_number){
	int position_begin = groups[group_number].rm_so;
	int position_end = groups[group_number].rm_eo;
	for(int i = position_begin; i < position_end; ++i)
		printf("%c", str[i]);
}

void print_name_and_command(regex_t *regex, char *buffer, regmatch_t *groups){
	while(fgets(buffer, SIZE_BUFFER, stdin) != NULL && strstr(buffer, LAST_STRING) == NULL)
		if(regexec(regex, buffer, COUNT_GROUPS, groups, 0) == 0){
			print_group(buffer, groups, 1);
			printf(" - ");
			print_group(buffer, groups, 2);
		}
}

int main(){
	char buffer[SIZE_BUFFER];
	regmatch_t groups[COUNT_GROUPS];
	regex_t regex;
	regcomp(&regex, REGEX_STRING, REG_EXTENDED);
	
	print_name_and_command(&regex, buffer, groups);
	
	regfree(&regex);
	return 0;
}
