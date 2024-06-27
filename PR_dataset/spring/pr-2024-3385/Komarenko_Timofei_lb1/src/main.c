#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define TXT_SIZE 200
#define REGEX "([a-z]+:\\/\\/)?(www\\.)?([a-zA-Z0-9_-]+\\.[a-z]+(\\.[a-z]+)*)\\/([a-zA-Z0-9_-]+\\/)*([a-zA-Z0-9_-]+\\.[a-z0-9]+)"


char* get_text(){
	size_t size = TXT_SIZE, id = 0; 
    char* txt = (char*)malloc(size*sizeof(char)); 
    
    if (!txt) {
        fprintf(stderr, "Memory allocation error\n");
        exit(0);
    }
    do {
		txt[id++] = getchar();
		if (id+1 == size) {
			char* ptr = txt;
			size += 100;
			txt = (char*)realloc(txt, size*sizeof(char));
			if (!txt) {
				free(ptr);
				fprintf(stderr, "Memory allocation error\n");
				exit(0);
			}
		}
	} while(!strstr(txt, "Fin."));
	txt[id] = '\0';
	return txt;
}

int main()
{
    char* txt = get_text();
    char* regexString = REGEX;
    int maxGroups = 7;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    
    if(regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("cant compile\n");
        free(txt);
        return 0;    
    }
    if(regexec(&regexCompiled, txt, maxGroups, groupArray, 0))
    {
        printf("no Matches\n");
        regfree(&regexCompiled);
        free(txt);
        return 0;
    }
    int new_line = 0;
	char* text_copy = txt;
	while (regexec(&regexCompiled, text_copy, maxGroups, groupArray, 0) == 0) {
		if (new_line++){ 
            printf("\n");
        }
		for (int i = 3; i < maxGroups; i+=3) {
			for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++){ 
                printf("%c", text_copy[j]);
            }
			if (i == 3){ 
                printf(" - ");
            }
		}
		text_copy += groupArray[0].rm_eo - 1;
    }
    regfree(&regexCompiled);
    free(txt);
    return 0; 

}




