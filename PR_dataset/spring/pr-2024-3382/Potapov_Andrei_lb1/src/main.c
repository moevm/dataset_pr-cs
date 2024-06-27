#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define BLOCK 100

int main() {
    size_t maxGroups = 3;
    char * regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+:\\s*~\\s*# (.+)\n";
    
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    
    regcomp(&regexCompiled, regexString, REG_EXTENDED);
    
    char buffer[BLOCK];
    while (!strstr(buffer, "Fin.")) {
		fgets(buffer, BLOCK, stdin);

		if (regexec(&regexCompiled, buffer, maxGroups, groupArray, 0) == 0) {
            for (size_t i = 1; i < maxGroups; i++) {
				if (groupArray[i].rm_so == -1)
					break;

				for (size_t j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++)
					printf("%c", buffer[j]);
				if (i==1) {
				    printf(" - ");
				}
			}
			printf("\n");
		}
	}
	regfree(&regexCompiled);
    return 0;
}
