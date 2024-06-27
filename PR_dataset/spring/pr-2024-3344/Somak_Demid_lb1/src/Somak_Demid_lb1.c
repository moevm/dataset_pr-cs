#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

int main(){
    char * regstr = "([A-Za-z]+:\\/\\/)?(www\\.)?([a-zA-Z0-9]+(\\.[a-zA-Z0-9]+)+)(\\/[a-zA-Z\\/]+)?\\/([A-Za-z]+\\.[a-zA-Z0-9]+)";
    size_t maxGroups = 7;

    regex_t reg;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&reg, regstr, REG_EXTENDED))
    {
        printf("Сan't compile regular expression\n");
        return 0;
    };

    char* str = malloc(sizeof(char) * 10000);

     while(1) {
    	fgets(str, 10000, stdin);

    	if (strncmp(str, "Fin.",4) == 0) break;

    	if(regexec(&reg, str, maxGroups, groupArray, 0) == 0){
        	for (size_t i = groupArray[3].rm_so; i < groupArray[3].rm_eo; i++) {
                printf("%c", str[i]);
            }

            printf(" - ");

            for (size_t j = groupArray[6].rm_so; j < groupArray[6].rm_eo; j++) {
                printf("%c", str[j]);
            }
            printf("\n");
    	}
	}
    regfree(&reg);
    free(str);
    return 0;
}
