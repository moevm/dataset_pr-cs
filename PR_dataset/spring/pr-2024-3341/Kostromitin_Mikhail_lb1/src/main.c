#include <regex.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>


int fillString(char** string);
void regexMatch(regex_t regex);
void printRegexGroup(char* string, regmatch_t group);

#define STEP 2

const char* regexBase = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: \?~ \?# (.*)";


int main(){
    regex_t regex;
    int check = regcomp(&regex, regexBase, REG_EXTENDED);

	if (check)
	{
		fprintf(stderr, "Couldn't compile.");
		return 1;
	}

	regexMatch(regex);
	
	regfree(&regex);

    return 0;
}


int fillString(char** string){
	int capacity = STEP;
	int size = 0;
	*string = (char*)malloc(sizeof(char) * STEP);
	char symb;
	while ((symb = getchar()) != '\n' && symb != EOF)
	{
		if (size + 1 == capacity)
		{
			capacity *= STEP;
			char* buf = (char*)realloc(*string, sizeof(char) * capacity);
			*string = buf;
		}
		(*string)[size++] = symb;
	}
	(*string)[size] = '\0';
	if (!strcmp(*string, "Fin.")){
		free(*string);
		return 1;
	}
	return 0;
}


void regexMatch(regex_t regex){
	char* string;
	while(!fillString(&string))
	{
		regmatch_t regexGroups[3];

		if (!regexec(&regex, string, 3, regexGroups, 0))
		{
			printRegexGroup(string, regexGroups[1]);
			printf(" - ");
			printRegexGroup(string, regexGroups[2]);
			printf("\n");
		}

		free(string);
	}

}


void printRegexGroup(char* string, regmatch_t group){
	for (int i = group.rm_so; i < group.rm_eo; i++)
	{
		printf("%c", string[i]);
	}
}
