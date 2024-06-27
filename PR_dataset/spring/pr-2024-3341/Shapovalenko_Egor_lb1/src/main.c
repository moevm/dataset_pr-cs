#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>

const char* pattern = "([a-z0-9]+\\:\\/\\/)?(www\\.)?(([a-z0-9\\.]+)?[a-z0-9]+\\.[a-z0-9]+)\\/(([a-z0-9\\/]+)?[a-z0-9]+\\/)?([a-z0-9]+\\.[a-z0-9]+)";

int isFin(char* string) {
	return (strcmp(string, "Fin.") == 0);
}

void input(char** string) {
	int used_memory = 0, allocated_memory = 1;
	char ch = ' ';
	while (ch != '\n') {
		ch = getchar();
		if(used_memory >= allocated_memory) {
			allocated_memory *= 2;
			(*string) = (char*)realloc(*string, allocated_memory * sizeof(char));
		}
		(*string)[used_memory] = ch;
		used_memory++;
		if(isFin(*string)) break;
	}
}

void printGroup(char* string, regmatch_t group) {
	for (int i = group.rm_so; i < group.rm_eo; i++) {
		printf("%c", string[i]);
	}
}


void checkString(char* string, regex_t regexCompiled) {
	regmatch_t groups[8];
	if (regexec(&regexCompiled, string, 8, groups, 0) == 0) {
		printGroup(string, groups[3]);
		printf(" - ");
		printGroup(string, groups[7]);
		printf("\n");
	}
}

int main() {
	regex_t regexCompiled;
	regcomp(&regexCompiled, pattern, REG_EXTENDED);

	while(1) {
		char* string = (char*)calloc(1, sizeof(char));
		input(&string);
		checkString(string, regexCompiled);
		if(isFin(string)) {
			break;
		}
	}

	return 0;
}