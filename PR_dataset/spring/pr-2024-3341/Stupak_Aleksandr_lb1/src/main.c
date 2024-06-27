#include <stdio.h>
#include <string.h>
#include <regex.h>

void printMatch (char* s, regmatch_t groupArray) {
    for(int i = groupArray.rm_so; i < groupArray.rm_eo; i++)
        printf("%c", s[i]);
}

int main () {
    size_t maxGroups = 10;
    char* regexString = "([A-z]+:\\/\\/)?(www\\.)?([A-z_-]+(\\.[A-z_-]+){1,})((\\/[A-z]+){1,})?(\\/([A-z]+\\.[A-z0-9]+\n))";
    
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("can't compile regular expression\n");
        return 0;
    }

    char s[100];
    while (fgets(s, 100, stdin)) {
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0) {
            printMatch(s, groupArray[3]);
            printf(" - ");
            printMatch(s, groupArray[8]);
        }
	}

    regfree(&regexCompiled);
    return 0;
}