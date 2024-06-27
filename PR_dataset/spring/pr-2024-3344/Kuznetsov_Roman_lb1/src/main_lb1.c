#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

int main(){
    char* text = (char*)malloc(sizeof(char) * 10000); 
    char* pattern = "((http|https|ftp):\\/\\/)?"  // 1-2
              "(www\\.)?" //  3
              "([a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)+)" //  4-5
              "(\\/[-a-zA-Z0-9:%_\\+.~#?&//=]*)?" // 6 
              "\\/([^\\/]+\\.[a-zA-Z0-9]+)"; // 7 

    regex_t regex;
    size_t max_group = 8;
    regmatch_t groupArray[max_group];
    regcomp(&regex, pattern, REG_EXTENDED);

    while(1) {
    	fgets(text, 10000, stdin);
    	char *newline = strchr(text, '\n');
    	
    	if (newline) *newline = '\0';
    	
    	if (strcmp(text, "Fin.") == 0) break;

    	if(regexec(&regex, text, max_group, groupArray, 0) == 0){
        	printf("%.*s - %.*s\n",
               	(int)(groupArray[4].rm_eo - groupArray[4].rm_so), &text[groupArray[4].rm_so],
               	(int)(groupArray[7].rm_eo - groupArray[7].rm_so), &text[groupArray[7].rm_so]);
    	}
	}
    regfree(&regex);
    return 0;
}
