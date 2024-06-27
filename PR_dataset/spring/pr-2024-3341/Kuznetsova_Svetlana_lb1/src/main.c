#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

#define END_STR '\0'
#define END_SENTENCE '\n'
#define LAST_STR "Fin."

const char* pattern = "(\\w+)@(\\w|-)+: ?~ ?# (.*)";

void input(char**);
void check(char*, regex_t);
void print(char*, regmatch_t*);

void input(char** string) {
	int capacity = 1, size = 0;
	char ch = getchar();
	while (ch != END_SENTENCE) {
		if (size + 1 >= capacity) {
			capacity = capacity * 2;
			(*string) = (char*)realloc(*string, capacity * sizeof(char));
		}
		(*string)[size++] = ch;
		(*string)[size] = END_STR;
		if (strcmp(*string, LAST_STR) == 0) break;
		ch = getchar();
	}
}

void check(char* string, regex_t regex_compiled) {
	regmatch_t group[4];
	if (regexec(&regex_compiled, string, 4, group, 0) == 0) {
		print(string, group);
	}
}

void print(char* string, regmatch_t* group) {
	string[group[1].rm_eo] = END_STR;
	string[group[3].rm_eo] = END_STR;
	printf("%s - %s\n", string + group[1].rm_so, string + group[3].rm_so);
}

int main() {
	regex_t regex_compiled;
	regcomp(&regex_compiled, pattern, REG_EXTENDED);
	char* str = NULL;
	input(&str);
	while (strcmp(str, LAST_STR)) {
		check(str, regex_compiled);
		input(&str);
	}
	return 0;
}