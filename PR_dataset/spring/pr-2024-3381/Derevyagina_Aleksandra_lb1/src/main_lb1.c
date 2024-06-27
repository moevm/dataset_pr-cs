#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <stdbool.h>

#define SIZE 100

int main(){
	regex_t regex;
	char* regexStr = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_\\-]+ ?: ?~ ?# ?(.+)";
	if (regcomp(&regex, regexStr, REG_EXTENDED) != 0){
		printf("Error\n");
		return 1;
	}
	size_t maxGroups = 3;
	regmatch_t groupArray[maxGroups];
	char* strs = (char*)calloc(SIZE, sizeof(char));
	while (true){
		fgets(strs, SIZE, stdin);
		int i;
		for (i = 0; strs[i] != '\n' && strs[i] != '\0'; i++){}
		strs[i] = '\0';
		if (!strcmp(strs, "Fin.")){
			break;
		}
		int status = regexec(&regex, strs, maxGroups, groupArray, 0);
		if (!status){
			strs[groupArray[1].rm_eo] = '\0';
			strs[groupArray[2].rm_eo] = '\0';
			printf("%s - %s\n", strs + groupArray[1].rm_so, strs + groupArray[2].rm_so);
		}
	}
	free(strs);
	regfree(&regex);
	return 0;
}
