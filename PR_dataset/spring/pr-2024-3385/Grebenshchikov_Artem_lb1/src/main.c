#include <stdio.h>
#include <regex.h>
#include <string.h>

#define COUNT_MATCHES 8
#define STR_SIZE 385



int main(){
    regex_t regex_compiled;
    regmatch_t matches[COUNT_MATCHES];
    char sentence[STR_SIZE];
    char* regex_str = "([A-Za-z]+:\\/\\/)?(www\\.)?([a-z]+(\\.[a-z]+)+)\\/([a-z]+(\\.[a-z]+)*\\/)*([A_Za-z0-9]+\\.[A-Za-z]+[A-za-z0-9]*)";
    if (regcomp(&regex_compiled, regex_str, REG_EXTENDED) != 0){
        printf("Failed to compile regex pattern\n");
        return 1;
    }
    while (fgets(sentence, STR_SIZE, stdin)){
        if (strcmp(sentence, "Fin.\n") == 0) {
            break;
        }
		if (regexec(&regex_compiled, sentence, COUNT_MATCHES, matches, 0) == 0){
            for(int j = matches[3].rm_so; j < matches[3].rm_eo; j++)
			    printf("%c",sentence[j]);
			printf(" - ");
			for(int j = matches[7].rm_so; j < matches[7].rm_eo; j++)
		    	printf("%c",sentence[j]);
		    printf("\n");
        }
    }
    regfree(&regex_compiled);
    return 0;
}
