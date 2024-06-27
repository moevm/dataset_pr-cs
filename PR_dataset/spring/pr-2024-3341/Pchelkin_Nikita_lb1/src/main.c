#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define BLOCK 100


void search(char* text, regex_t regexCompiled, size_t maxGroups, regmatch_t groupArray[]){
    if (regexec(&regexCompiled, text, maxGroups, groupArray, 0) == 0){
    	for(int k = groupArray[3].rm_so; k < groupArray[3].rm_eo; k++) printf("%c", text[k]);
        printf(" - ");
        for(int k = groupArray[6].rm_so; k < groupArray[6].rm_eo; k++) printf("%c", text[k]);
        printf("\n");
	}
}


int main(){

	char text[BLOCK];

    char* regexString = "([a-z]+:\\/\\/)?(www\\.)?(([a-z]+\\.)+[a-z]+)\\/([a-z]+\\/)*([a-z]+\\.[a-z0-9]+)";
    regex_t regexCompiled;
    size_t maxGroups = 7;

    regcomp(&regexCompiled, regexString, REG_EXTENDED);
    regmatch_t groupArray[maxGroups];

	while(fgets(text, BLOCK, stdin)){
		if(strcmp(text, "Fin.") == 0) break;
		search(text, regexCompiled, maxGroups, groupArray);
	}
    
    return 0;
}
