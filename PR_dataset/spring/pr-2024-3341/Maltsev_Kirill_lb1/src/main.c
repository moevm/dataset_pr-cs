#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

const char* pattern = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.*)";

void inputString(char**);
int inputInterruption(char*);
void checkString(char*, regex_t);
void checkString(char*, regex_t);
void printGroup(char*, regmatch_t);


int main() {
	regex_t regexCompiled;
	regcomp(&regexCompiled, pattern, REG_EXTENDED);

	while (1) {
		char* string = NULL;
		inputString(&string);
		checkString(string, regexCompiled);
		if (inputInterruption(string)) {
			break;
		}
	}
}

void inputString(char** string) {
	int size = 0, capacity = 0;
	char ch = 0;
	while (ch != '\n') {
		ch = getchar();
		while (size + 1 >= capacity) {
			if (capacity == 0) {
				capacity = 1;
			}
			capacity *= 2;
			(*string) = (char*) realloc(*string, capacity*sizeof(char));
		}
		(*string)[size++] = ch;
		(*string)[size] = '\0';
		if (inputInterruption(*string)) break;
	}
}

int inputInterruption(char* string) {
	return (strcmp(string, "Fin.") == 0);
}

void checkString(char* string, regex_t regexCompiled) {
	regmatch_t groups[3];
	if (regexec(&regexCompiled, string, 3, groups, 0) == 0) {
		printGroup(string, groups[1]);
		printf(" - ");
		printGroup(string, groups[2]);
	}
}

void printGroup(char* string, regmatch_t group) {
	for (int i=group.rm_so; i<group.rm_eo; i++) {
		printf("%c", string[i]);
	}
}