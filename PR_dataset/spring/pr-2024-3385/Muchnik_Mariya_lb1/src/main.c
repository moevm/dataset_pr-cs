#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define TXT_SIZE 200
#define REG "([a-z]+:\\/\\/)?(www\\.)?([a-zA-Z0-9_-]+\\.[a-z]+(\\.[a-z]+)*)\\/([a-zA-Z0-9_-]+\\/)*([a-zA-Z0-9_-]+\\.[a-z0-9]+)"

char* get_text(){
	size_t size = TXT_SIZE, id = 0; 
    char* text = (char*)malloc(size*sizeof(char)); 
    if (!text) {
        fprintf(stderr, "Memory allocation error\n");
        exit(0);
    }
    do {
		text[id++] = getchar();
		if (id+1 == size) {
			char* ptr = text;
			size += 100;
			text = (char*)realloc(text, size*sizeof(char));
			if (!text) {
				free(ptr);
				fprintf(stderr, "Memory allocation error\n");
				exit(0);
			}
		}
	} while(!strstr(text, "Fin."));
	text[id] = '\0';
	return text;
}

int main(){ 
	char* text = get_text();

	char* regexString = REG;
	size_t maxGroup = 7;

	regex_t regexCompiled;
	regmatch_t groupArray[maxGroup];

	if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
		fprintf(stderr, "Can't compile regular expression");
		free(text);
		return 0;
	}

	if(regexec(&regexCompiled, text, maxGroup, groupArray, 0)){
		printf("No matches\n");
		regfree(&regexCompiled);
		free(text);
		return 0; 
	}
    
    int flag = 0;
	char* text_copy = text;
	while (regexec(&regexCompiled, text_copy, maxGroup, groupArray, 0) == 0) {
		if (flag++) printf("\n");
		for (int i = 3; i < maxGroup; i+=3) {
			for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++) printf("%c", text_copy[j]);
			if (i == 3) printf(" - ");
		}
		text_copy += groupArray[0].rm_eo - 1;
    }

    regfree(&regexCompiled);
         free(text);
    return 0; 
}
