#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

#define INPUT_SIZE 100    
#define NUM_INPUTS 100     

void printMatch(char* s, regmatch_t groupArray) {
    for (int i = groupArray.rm_so; i < groupArray.rm_eo; i++)
        printf("%c", s[i]);
}

int main() {
    size_t maxGroups = 100;
    char* regexString = "([A-z]+:\\/\\/)?(w{3}\\.)?([A-z_-]+(\\.[A-z_-]+){1,})((\\/[A-z]+){1,})?(\\/([A-z]+\\.[A-z0-9]+\n))";
    regex_t regexCompiled;
    char s[NUM_INPUTS][INPUT_SIZE];    
    int numInputs = 0;                

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("can't compile regular expression\n");
        return 0;
    }

    while (fgets(s[numInputs], INPUT_SIZE, stdin) && numInputs < NUM_INPUTS) {
        if (strstr(s[numInputs], "Fin.") != NULL){
            break;
        }
        numInputs++;
    }

    regmatch_t groupArray[maxGroups];
    

    for (int i = 0; i < numInputs; i++) {
        if (regexec(&regexCompiled, s[i], maxGroups, groupArray, 0) == 0) {
            printMatch(s[i], groupArray[3]); 
            printf(" - ");
            if (groupArray[8].rm_so != -1) { 
                printMatch(s[i], groupArray[8]); 
            }
        }
    }

    regfree(&regexCompiled);

    return 0;
}