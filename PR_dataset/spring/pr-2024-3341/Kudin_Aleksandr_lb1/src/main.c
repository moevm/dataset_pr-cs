#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


const char* URL_PATTERN = "([a-z]+\\:\\/\\/)?(www\\.)?(([a-z]+\\.)+[a-z]+)\\/([a-z]+\\/)*([a-z]+\\.[a-z0-9]+)";
const int GROUPS_COUNT = 7;
const int BUFFER_LENGTH = 1000;
const char* END_OF_INPUT = "Fin.";

void displayMatches(char* text, regmatch_t* matches);

int main() {
    regex_t regexCompiled;
    regmatch_t matchGroups[GROUPS_COUNT];
    char inputBuffer[BUFFER_LENGTH];
    
    regcomp(&regexCompiled, URL_PATTERN, REG_EXTENDED);

    while(fgets(inputBuffer, BUFFER_LENGTH, stdin)) {
        if(strncmp(inputBuffer, END_OF_INPUT, strlen(END_OF_INPUT)) == 0) break;

        if(regexec(&regexCompiled, inputBuffer, GROUPS_COUNT, matchGroups, 0) == 0) {
            displayMatches(inputBuffer, matchGroups);
        }
    }
    regfree(&regexCompiled);
    return 0;
}

void displayMatches(char* text, regmatch_t* matches) {
    printf("%.*s - %.*s\n",
           (int)(matches[3].rm_eo - matches[3].rm_so), &text[matches[3].rm_so],
           (int)(matches[6].rm_eo - matches[6].rm_so), &text[matches[6].rm_so]);
}
