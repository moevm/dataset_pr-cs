#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>


int main() {

    char * regexString = "([A-Za-z0-9\\_]+)@[A-Za-z0-9\\_-]+\\: ?\\~ ?\\# (.+)\n";
    int count = 0;
    size_t maxGroups = 3;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("Wowm no - can't compile regular expression\n");
        return 0;
    }
    char *s = calloc(100, sizeof(char));
    while (!strstr(s,"Fin.")) {

        fgets(s, 100, stdin);

        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0){
            count+=1;
            if (count != 1){
              printf("\n");
            }

            for (int i = 1; i < maxGroups; i++){
                for(int j=groupArray[i].rm_so;j<groupArray[i].rm_eo;j++){
                    printf("%c", s[j]);
                }

                if(i == 1)
                printf(" - ");
            }

        }

    }

    free(s);
    regfree(&regexCompiled);
    return 0;
}
