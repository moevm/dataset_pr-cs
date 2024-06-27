#include <stdio.h>
#include <string.h>
#include <regex.h>

int main() {
    char text[10000];
    char input[10000] = "";
    char *regexString = "((http|https|ftp):\\/\\/)?(www\\.)?(([a-zA-Z]+\\.)+[a-zA-Z]+)(\\/[a-zA-Z]+)*(\\/([a-zA-Z]+\\.[a-zA-Z0-9_+=!-]+))";
    regex_t regex;
    regmatch_t groupArray[9];
    int match;

    regcomp(&regex, regexString, REG_EXTENDED);

    while (1) {
        fgets(text, 10000, stdin);

        if (strstr(text, "Fin.") != NULL)
            break;

        strcat(input, text);
    }
    char *url = input;
    int urlCount = 0;
    while (1) {
        match = regexec(&regex, url, 9, groupArray, 0);
        if (match == REG_NOMATCH)
            break;

        if (groupArray[4].rm_so != -1 && groupArray[4].rm_eo != -1 &&
            groupArray[8].rm_so != -1 && groupArray[8].rm_eo != -1) {
            printf("%.*s - %.*s\n",
                   (int)(groupArray[4].rm_eo - groupArray[4].rm_so),
                   url + groupArray[4].rm_so,
                   (int)(groupArray[8].rm_eo - groupArray[8].rm_so),
                   url + groupArray[8].rm_so);
        }
        
        url += groupArray[0].rm_eo;
        urlCount++;
    }

    if (urlCount == 0) {
        printf("No URLs found.\n");
    }
    
    regfree(&regex);
    return 0;
}