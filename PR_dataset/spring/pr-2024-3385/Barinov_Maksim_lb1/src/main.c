#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define SB 100

int main() {
	char* patern = "([0-9a-zA-Z_]+)@[a-zA-Z0-9_-]+: *~ *# (.*)";
	int maxGroups = 3;
	//char* patern = "([0-9a-zA-z_]+)";
	regex_t regexCompiled;
	regmatch_t groupArray[maxGroups];
	if (regcomp(&regexCompiled, patern, REG_EXTENDED)) {
		printf("Error");
		return 0;
	}
	char* a = calloc(SB, sizeof(char));
	char* s = "Fin.";
	char c = ' ';
	int cnt = 1, i = 0;
	while (strcmp(a, s) != 0) {
		c = getchar();
		if (c == '\n'){
			if (regexec(&regexCompiled, a, maxGroups, groupArray, 0) == 0) {
				for(int j = groupArray[1].rm_so; j < groupArray[1].rm_eo;j++) {
					printf("%c", a[j]);
				}
				printf(" - ");
				for(int j = groupArray[2].rm_so; j < groupArray[2].rm_eo;j++) {
					printf("%c", a[j]);
				}
				printf("\n");
			}
			free(a);
			a = calloc(SB, sizeof(char));
			cnt = 1, i = 0;
		} else {
			a[i] = c;
			if (i + 1 >= SB * cnt) {
				a = realloc(a, SB * (cnt + 1));
				cnt++;
			}
			i++;
		}
	}
}
